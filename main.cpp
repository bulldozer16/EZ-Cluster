#include "filter.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define MASTER	0

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	int nodes = 1;
	char *img_path = "/home/mpiuser/cloud/lena.jpeg";

	if (argc > 1)
	{
		img_path = argv[1]; 
	}	
	
	int num_tasks, rank, rc;
	char out_msg, in_msg;
	
	MPI_Status status;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	nodes = num_tasks;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == MASTER)
	{
		char processor_name[MPI_MAX_PROCESSOR_NAME];
    		int name_len;
    		MPI_Get_processor_name(processor_name, &name_len);
		printf("Master is %s\n", processor_name);

		rc = cargar_imagen(img_path);
		if (!rc)
		{
			return -1;
		}
		
		split(nodes);

		out_msg = 'S';
		clock_t start = clock();

		for (int i = 1; i < num_tasks; i++)
		{
			rc = MPI_Send(&out_msg, 1, MPI_CHAR, i, 1, MPI_COMM_WORLD);
			printf("Start signal sent to slave %d\n", i);
		}

                dilate(MASTER);

		for (int i = 1; i < num_tasks; i++)
		{
			rc = MPI_Recv(&in_msg, 1, MPI_CHAR, i, 1, MPI_COMM_WORLD, &status);
			printf("Ready signal received from slave %d\n", i);
		}

		merge(nodes);

		clock_t end = clock();
        	double elapsed = (end - start) / (double) CLOCKS_PER_SEC;
		
		printf("Elapsed time: %f seconds\n", elapsed);
		
		double bw = bandwidth(nodes, img_path, elapsed);
		printf("Bandwidth: %f MB/s\n", bw);
		show(nodes);
	}
	else
	{
		char processor_name[MPI_MAX_PROCESSOR_NAME];
    		int name_len;
    		MPI_Get_processor_name(processor_name, &name_len);

		printf("Slave %d is %s\n", rank, processor_name);

		rc = MPI_Recv(&in_msg, 1, MPI_CHAR, MASTER, 1, MPI_COMM_WORLD, &status);
		printf("Start signal received in slave %d\n", rank);


		dilate(rank);

		out_msg = 'R';
		rc = MPI_Send(&out_msg, 1, MPI_CHAR, MASTER, 1, MPI_COMM_WORLD);
		printf("Ready signal sent from slave %d\n", rank);
	}

	MPI_Finalize();
}
