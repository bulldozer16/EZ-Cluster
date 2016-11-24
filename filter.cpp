#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

Mat img_color, img_input, img_output, img_node0, img_node1, img_node2, img_node3, img_node4, img_node5, img_node6, img_node7;

int cargar_imagen(char *direccion) 
{
	img_color = imread(direccion, 1);
      	img_input = imread(direccion, 0);
      	img_output = imread(direccion, 0);

        if (img_input.empty()) 
	{
          	printf("Fallo de lectura: imagen no encontrada o sin contenido\n");
            	return 0;
        } 
	else 
	{
            	return 1;
        }
}

void dilate(int node) 
{
      	Mat img_in;
        if (node == 0) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
        } 
	else if (node == 1) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
        } 
	else if (node == 2) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
        } 
	else if (node == 3) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
        } 
	else if (node == 4) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node4.jpg", 0);
        } 
	else if (node == 5) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node5.jpg", 0);
	} 
	else if (node == 6) 
	{
            	img_in = imread("/home/mpiuser/cloud/img_node6.jpg", 0);
        } 
	else
	{
            	img_in = imread("/home/mpiuser/cloud/img_node7.jpg", 0);
        }

        int row = img_in.rows - 4;
        int col = img_in.cols - 4;
        Mat img_out(row, col, CV_8UC1, Scalar(0));
        int indicerow = 0;
        int indicecol = 0;
        unsigned char *input = (unsigned char*) (img_in.data);
        unsigned char *temp = (unsigned char*) (img_out.data);
        int indice5;

        for (int i = 0; i < row; i++) 
	{
            	indice5 = i;
            	int a, b, c, d, e;
            	for (int j = 0; j < 5; j++) 
		{
                	for (int k = 0; k < col;) 
			{
                    		a = input[img_in.step * indice5 + k];
                    		b = input[img_in.step * indice5 + k + 1];
                    		c = input[img_in.step * indice5 + k + 2];
                    		d = input[img_in.step * indice5 + k + 3];
                    		e = input[img_in.step * indice5 + k + 4];
                    		int list[5] = {a, b, c, d, e};
                    		int max = 0;
                    		for (int x = 0; x < 5; x++) 
				{
                        		if (max < list[x]) 
					{
                            			max = list[x];
                        		}
                    		}
                    		if (temp[img_out.step * indicerow + indicecol] < max) 
				{
                        		temp[img_out.step * indicerow + indicecol] = max;
                    		}
                    		indicecol++;
                    		k++;
	            	}
                	indice5++;
                	indicecol = 0;
            	}
            	indicerow++;
        }

        if (node == 0) 
	{
            	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_out);
        } 
	else if (node == 1) 
	{
            	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_out);
        } 
	else if (node == 2) 
	{
            	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_out);
        } 
	else if (node == 3) 
	{
            	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_out);
        } 
	else if (node == 4) 
	{
            	imwrite("/home/mpiuser/cloud/img_node4.jpg", img_out);
        } 
	else if (node == 5) 
	{
            	imwrite("/home/mpiuser/cloud/img_node5.jpg", img_out);
        } 
	else if (node == 6) 
	{
            	imwrite("/home/mpiuser/cloud/img_node6.jpg", img_out);
        } 
	else
	{
            	imwrite("/home/mpiuser/cloud/img_node7.jpg", img_out);
        }
}

void split(int nodes) 
{
    	int filas = img_input.rows;
        int num_split;
        switch (nodes) 
	{
        	case 1:
            	{
                	img_node0 = img_input.rowRange(0, filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);

                	break;
            	}
            	case 2:
            	{
                	num_split = filas / 2;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);

                	break;
            	}
            	case 3:
            	{
                	num_split = filas / 3;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);

                	break;
            	}
            	case 4:
            	{
                	num_split = filas / 4;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), (num_split * 3 + 2));
                	img_node3 = img_input.rowRange((num_split * 3 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);
                	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_node3);

                	break;
            	}
            	case 5:
            	{
                	num_split = filas / 5;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), (num_split * 3 + 2));
                	img_node3 = img_input.rowRange((num_split * 3 - 2), (num_split * 4 + 2));
	                img_node4 = img_input.rowRange((num_split * 4 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);
                	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_node3);
                	imwrite("/home/mpiuser/cloud/img_node4.jpg", img_node4);

                	break;
            	}
            	case 6:
            	{
                	num_split = filas / 6;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), (num_split * 3 + 2));
                	img_node3 = img_input.rowRange((num_split * 3 - 2), (num_split * 4 + 2));
                	img_node4 = img_input.rowRange((num_split * 4 - 2), (num_split * 5 + 2));
                	img_node5 = img_input.rowRange((num_split * 5 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);
                	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_node3);
                	imwrite("/home/mpiuser/cloud/img_node4.jpg", img_node4);
                	imwrite("/home/mpiuser/cloud/img_node5.jpg", img_node5);

                	break;
            	}
            	case 7:
            	{
                	num_split = filas / 7;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), (num_split * 3 + 2));
                	img_node3 = img_input.rowRange((num_split * 3 - 2), (num_split * 4 + 2));
                	img_node4 = img_input.rowRange((num_split * 4 - 2), (num_split * 5 + 2));
                	img_node5 = img_input.rowRange((num_split * 5 - 2), (num_split * 6 + 2));
                	img_node6 = img_input.rowRange((num_split * 6 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);
                	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_node3);
                	imwrite("/home/mpiuser/cloud/img_node4.jpg", img_node4);
                	imwrite("/home/mpiuser/cloud/img_node5.jpg", img_node5);
                	imwrite("/home/mpiuser/cloud/img_node6.jpg", img_node6);

                	break;
            	}
            	case 8:
            	{
                	num_split = filas / 8;

                	img_node0 = img_input.rowRange(0, num_split + 2);
                	img_node1 = img_input.rowRange(num_split - 2, (num_split * 2 + 2));
                	img_node2 = img_input.rowRange((num_split * 2 - 2), (num_split * 3 + 2));
                	img_node3 = img_input.rowRange((num_split * 3 - 2), (num_split * 4 + 2));
                	img_node4 = img_input.rowRange((num_split * 4 - 2), (num_split * 5 + 2));
                	img_node5 = img_input.rowRange((num_split * 5 - 2), (num_split * 6 + 2));
                	img_node6 = img_input.rowRange((num_split * 6 - 2), (num_split * 7 + 2));
                	img_node7 = img_input.rowRange((num_split * 7 - 2), filas);

                	imwrite("/home/mpiuser/cloud/img_node0.jpg", img_node0);
                	imwrite("/home/mpiuser/cloud/img_node1.jpg", img_node1);
                	imwrite("/home/mpiuser/cloud/img_node2.jpg", img_node2);
                	imwrite("/home/mpiuser/cloud/img_node3.jpg", img_node3);
                	imwrite("/home/mpiuser/cloud/img_node4.jpg", img_node4);
                	imwrite("/home/mpiuser/cloud/img_node5.jpg", img_node5);
                	imwrite("/home/mpiuser/cloud/img_node6.jpg", img_node6);
                	imwrite("/home/mpiuser/cloud/img_node7.jpg", img_node7);

                	break;
            	}
            	default:
                	break;
        }
}

void show(int nodes) 
{
	switch (nodes) 
	{
            	case 1:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("FINAL", img_output);
                	waitKey(0);
			break;
            	case 2:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
			img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	imshow("Image node 1", img_node1);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
            	case 3:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("FINAL", img_output);
                	waitKey(0);
	            	break;
            	case 4:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("Image node 3", img_node3);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
            	case 5:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("Image node 3", img_node3);
                	imshow("Image node 4", img_node4);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
             	case 6:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("Image node 3", img_node3);
                	imshow("Image node 4", img_node4);
                	imshow("Image node 5", img_node5);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
            	case 7:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("Image node 3", img_node3);
                	imshow("Image node 4", img_node4);
                	imshow("Image node 5", img_node5);
                	imshow("Image node 6", img_node6);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
            	case 8:
                	imshow("Input", img_color);
                	imshow("Image node 0", img_node0);
                	imshow("Image node 1", img_node1);
                	imshow("Image node 2", img_node2);
                	imshow("Image node 3", img_node3);
                	imshow("Image node 4", img_node4);
                	imshow("Image node 5", img_node5);
                	imshow("Image node 6", img_node6);
                	imshow("Image node 7", img_node7);
                	imshow("FINAL", img_output);
                	waitKey(0);
                	break;
            	default:
                	break;
	}
}

double bandwidth(int nodes, char *path, double time) 
{
    	int bits = 0;
        if (nodes == 1) 
	{
	 	return bits;
        } 
	else 
	{
            	FILE * f = fopen(path, "r");
            	fseek(f, 0, SEEK_END);
            	double img_in_size = (double) ftell(f);
            	img_in_size = img_in_size / (1000000);
            	fclose(f);
            	double img_fragment = ((img_in_size / nodes) * (nodes - 1) * 2) + (((nodes - 1) * 2) / 1000000);
            	img_fragment = img_fragment / time;
            	return img_fragment;
    	}
}

void merge(int nodes) 
{
   	switch (nodes) 
	{
            	case 1:
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_output = img_node0;
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	case 2:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 3:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 4:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node3 = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	img_node3 = img_node3.rowRange(0, img_node3.rows);
                	vconcat(img_output, img_node3, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 5:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node3 = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
                	img_node4 = imread("/home/mpiuser/cloud/img_node4.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	img_node3 = img_node3.rowRange(0, img_node3.rows);
                	vconcat(img_output, img_node3, img_output);
                	img_node4 = img_node4.rowRange(0, img_node4.rows);
                	vconcat(img_output, img_node4, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 6:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node3 = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
                	img_node4 = imread("/home/mpiuser/cloud/img_node4.jpg", 0);
                	img_node5 = imread("/home/mpiuser/cloud/img_node5.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	img_node3 = img_node3.rowRange(0, img_node3.rows);
	            	vconcat(img_output, img_node3, img_output);
                	img_node4 = img_node4.rowRange(0, img_node4.rows);
                	vconcat(img_output, img_node4, img_output);
                	img_node5 = img_node5.rowRange(0, img_node5.rows);
                	vconcat(img_output, img_node5, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 7:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node3 = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
                	img_node4 = imread("/home/mpiuser/cloud/img_node4.jpg", 0);
                	img_node5 = imread("/home/mpiuser/cloud/img_node5.jpg", 0);
                	img_node6 = imread("/home/mpiuser/cloud/img_node6.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	img_node3 = img_node3.rowRange(0, img_node3.rows);
                	vconcat(img_output, img_node3, img_output);
                	img_node4 = img_node4.rowRange(0, img_node4.rows);
                	vconcat(img_output, img_node4, img_output);
                	img_node5 = img_node5.rowRange(0, img_node5.rows);
                	vconcat(img_output, img_node5, img_output);
                	img_node6 = img_node6.rowRange(0, img_node6.rows);
                	vconcat(img_output, img_node6, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	case 8:
            	{
                	img_node0 = imread("/home/mpiuser/cloud/img_node0.jpg", 0);
                	img_node1 = imread("/home/mpiuser/cloud/img_node1.jpg", 0);
                	img_node2 = imread("/home/mpiuser/cloud/img_node2.jpg", 0);
                	img_node3 = imread("/home/mpiuser/cloud/img_node3.jpg", 0);
                	img_node4 = imread("/home/mpiuser/cloud/img_node4.jpg", 0);
                	img_node5 = imread("/home/mpiuser/cloud/img_node5.jpg", 0);
                	img_node6 = imread("/home/mpiuser/cloud/img_node6.jpg", 0);
                	img_node7 = imread("/home/mpiuser/cloud/img_node7.jpg", 0);
                	img_node0 = img_node0.rowRange(0, img_node0.rows);
                	img_node1 = img_node1.rowRange(0, img_node1.rows);
                	vconcat(img_node0, img_node1, img_output);
                	img_node2 = img_node2.rowRange(0, img_node2.rows);
                	vconcat(img_output, img_node2, img_output);
                	img_node3 = img_node3.rowRange(0, img_node3.rows);
                	vconcat(img_output, img_node3, img_output);
                	img_node4 = img_node4.rowRange(0, img_node4.rows);
                	vconcat(img_output, img_node4, img_output);
                	img_node5 = img_node5.rowRange(0, img_node5.rows);
                	vconcat(img_output, img_node5, img_output);
                	img_node6 = img_node6.rowRange(0, img_node6.rows);
                	vconcat(img_output, img_node6, img_output);
                	img_node7 = img_node7.rowRange(0, img_node7.rows);
                	vconcat(img_output, img_node7, img_output);
                	imwrite("/home/mpiuser/cloud/final.jpg", img_output);
                	break;
            	}
            	default:
			break;
        }
}
