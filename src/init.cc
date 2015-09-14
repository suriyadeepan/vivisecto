#include "stdio.h"
#include "opencv2/opencv.hpp"

#include "simulator/model.h"
#include "simulator/view.h"
#include "simulator/controller.h"

#define SIM_DIX 200
#define SIM_DIY 200

using namespace cv;

Node** nodes = NULL;
Mat view;

/*
  the line read from the file is passed and node is created if not already existing 
  or updated otherwise with the currently read parameters
*/
int add_to_array(Node* array[], int len, char* string){
  double time;
  int id, x, y, t, s;
  if (6 != sscanf(string, "%lf %d %d %d %d %d", &time, &id, &t, &x, &y, &s))
    return -1;

  if (id >= len)
    return -1;

	//printf("\nParams: %lf %d %d %d %d %d", time, id, x, y, t, s);

//	printf("\n%x",array[id]);

  if (array[id] == NULL) {
    array[id] = Node_new(id, x ,y, t, s);
    if (array[id] == NULL)
      printf("Error allocating memory... exiting...\n"), exit(1);
  } else {

		switch(t) {

			case 0:
				array[id]->x = x;
				array[id]->y = y;
				break;

			case 1:
				++array[id]->pkts_tx;
				break;

			case 2:
				++array[id]->pkts_rx;
		}
		array[id]->sender = s;
		array[id]->ev_type = t;
 }

  return id;
}

int main(int argc, char** argv){

  static const char filename[] = "events.mono";
  FILE *fp = fopen ( filename, "r" );

  // initiate model
  Mat model;

  int node_count = model_init(fp);
  nodes = (Node**)malloc(sizeof(*nodes) * node_count);

  for (int i = 0; i < node_count; i++)
		nodes[i] = NULL;

	// init view
	view_x4(&view,SIM_DIX,SIM_DIY);
	
  
  char line [60]; 
  double sim_t, sim_prev=-1;
	
  fgets (line, sizeof line, fp);
  sscanf(line, "%lf", &sim_t);
  sim_prev = sim_t;
  int line_no = 1;

	char user_ip = ' ';
	int delay = 1;

  do {
    sscanf(line, "%lf", &sim_t);


    if (sim_t > sim_prev) {

			// redraw View
			view_drawRadioComm(&view,nodes,node_count);
			view_drawNodes(&view,nodes,node_count,sim_t);
			// Smooth
			blur( view, view, Size( 4, 4 ) );

			// delay
			waitKey(delay);

			// get user input
			user_ip = (char)waitKey(delay);

			cntl_input(user_ip,&delay);
			
			// update display
			imshow("View Mode",view);
		}

    sim_prev = sim_t;
    add_to_array(nodes, node_count, line);
    line_no++;

  } while (fgets (line, sizeof line, fp) != NULL && user_ip != 'q');


  int i;
  for (i = 0; i < node_count; i++)
    free(nodes[i]);
  

  return 0;

}
