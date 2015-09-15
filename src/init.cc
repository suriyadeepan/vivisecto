#include "stdio.h"
#include "opencv2/opencv.hpp"

#include "simulator/model.h"
#include "simulator/view.h"
#include "simulator/controller.h"
#include "map/map.h"
#include "index.h"

#define SIM_DIX 200
#define SIM_DIY 200

using namespace cv;

Node** nodes = NULL;
Mat view_map;
Mat view;

// Frame switch delay
int delay = 1;

// total number of steps of sim_t in trackbar
int SIM_STEPS;
int sim_seek_step = 0;
FILE *ifp;
FILE *fp;

bool ON_FILE_READ = false;
bool ON_SEEK = false;

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


void cntl_simTimeSeek( int val, void* ){

		ON_SEEK = true;
		sim_seek_step = val;
		printf("\nSIM_T : %d",val);
		while(ON_FILE_READ);
		model_seek(fp,ifp,val);
		ON_SEEK = false;

}

void cntl_mouseClicked(int event, int x, int y, int flags, void* userdata){
	
	if ( event == EVENT_LBUTTONDOWN ){
		if(delay != -1){
			printf("\n>> PAUSED");
			printf("\n>> Press any key to continue");
			delay = -1;
		}
		else{
			printf("\n>> PLAY : Press any key to continue");
			delay = 1;
		}
	}

	if ( event == EVENT_RBUTTONDOWN ){
		destroyWindow("View Mode");
		exit(-1);
	}



}

int main(int argc, char** argv){

  char  filename[] = "events.mono";
  char ifilename[] = "events.index";
  fp = fopen ( filename, "r" );

	// index events.mono 
	SIM_STEPS = index_index(filename);
	printf("\nSIM_STEPS : %d",SIM_STEPS);

	// open index file in RO mode
	ifp = fopen(ifilename,"r");

  int node_count = model_init(fp);
  nodes = (Node**)malloc(sizeof(*nodes) * node_count);

  for (int i = 0; i < node_count; i++)
		nodes[i] = NULL;

	// init view
	view_x4(&view_map,SIM_DIX,SIM_DIY);
	map_drawGrid(&view_map);
  
  char line [60]; 
  double sim_t, sim_prev=-1;
	
  fgets (line, sizeof line, fp);
  sscanf(line, "%lf", &sim_t);
  sim_prev = sim_t;
  int line_no = 1;

	char user_ip = ' ';

	namedWindow("View Mode", 1);
	// setup track bar to seek sim_t
	createTrackbar( "Simulation Time", "View Mode", &sim_seek_step,  SIM_STEPS, cntl_simTimeSeek );
	//set the callback function for any mouse event
	setMouseCallback("View Mode", cntl_mouseClicked, NULL);


  do {
		
		ON_FILE_READ = false;
    sscanf(line, "%lf", &sim_t);
 
    if (sim_t > sim_prev) {

			if(!ON_SEEK){
				sim_seek_step = (int)sim_t;
				setTrackbarPos("Simulation Time","View Mode",sim_seek_step);
			}

			// redraw View
			view_map.copyTo(view);
			view_drawRadioComm(&view,nodes,node_count);
			view_drawNodes(&view,nodes,node_count);
			blur( view, view, Size( 2, 2 ) );

			view_drawStats(&view,nodes,node_count,sim_t);
			view_drawModel(&view,nodes,node_count);
			blur( view, view, Size( 3, 3 ) );

			// get user input
			user_ip = (char)waitKey(delay);

			//cntl_input(user_ip,&delay);
			
			// update display
			imshow("View Mode",view);
		}

    sim_prev = sim_t;
    add_to_array(nodes, node_count, line);
    line_no++;

		ON_FILE_READ = true;	
  } while (fgets (line, sizeof line, fp) != NULL && user_ip != 'q');


  int i;
  for (i = 0; i < node_count; i++)
    free(nodes[i]);
  

  return 0;

}
