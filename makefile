main: main.cpp
	mpic++ -w main.cpp -o /home/mpiuser/app `pkg-config --cflags --libs opencv`

clean:
	rm -f /home/mpiuser/app img_node0.jpg img_node1.jpg img_node2.jpg img_node3.jpg img_node4.jpg img_node5.jpg img_node6.jpg img_node7.jpg final.jpg
