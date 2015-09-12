#include "stdio.h"
#include "opencv2/opencv.hpp"

#include "simulator/helper.h"
#include "simulator/model.h"

using namespace cv;

Node** nodes = NULL;

/*
  the line read from the file is passed and node is created if not already existing 
  or updated otherwise with the currently read parameters
*/
int add_to_array(Node* array[], int len, char* string){
  double time;
  int id, x, y, t, s;
  if (6 != sscanf(string, "%lf %d %d %d %d %d", &time, &id, &x, &y, &t, &s))
    return -1;

  if (id >= len)
    return -1;

  if (array[id] == NULL) {
    array[id] = Node_new(id, x ,y, t, s);
    if (array[id] == NULL)
      printf("Error allocating memory... exiting...\n"), exit(1);
  } else {
    array[id]->x = x;
    array[id]->y = y;
    array[id]->ev_type = t;
    array[id]->sender = s;
  }

  switch(t) {
  case 1:
    ++array[id]->pkts_tx;
    break;
  case 2:
    ++array[id]->pkts_rx;
    break;
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
  
  char line [60]; 
  double sim_t, sim_prev=-1;
	
  fgets (line, sizeof line, fp);
  sscanf(line, "%lf", &sim_t);
  sim_prev = sim_t;
  int line_no = 1;
  do {
    sscanf(line, "%lf", &sim_t);
    
    if (sim_t > sim_prev) {
      //draw(nodes);
      //delay(1000);
      unsigned int i;
      for (i = 0; i < node_count; i++)
	//Node_print(nodes[i]);
      
      printf("##################### %d  ##########################\n", line_no);
    }

    sim_prev = sim_t;
    add_to_array(nodes, node_count, line);
    line_no++;
  } while (fgets (line, sizeof line, fp) != NULL);



  int i;
  for (i = 0; i < node_count; i++)
    free(nodes[i]);
  
  fclose(fp);
  return 0;

}
