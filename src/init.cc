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
  int id, x, y, t, s;
  if (5 != sscanf(string, "%d %d %d %d %d %d", &id, &x, &y, &t, &s))
    return NULL;

  if (array[id] == NULL) {
    array[id] = Node_new(id, x ,y, t, s);
    if (array[id] == NULL)
      printf("Error allocating memory... exiting...\n"), exit(1)
	} else {
    array[id]->x = x;
    array[id]->y = y;
    array[id]->t = t;
    array[id]->sender = s;
  }

  return id;
}

int main(int argc, char** argv){

  static const char filename[] = "events.mono";
  FILE *fp = fopen ( filename, "r" );

  // initiate model
  Mat model;

  int num_nodes = model_init(ffp,&model);
  nodes = (Node**)malloc(sizeof (*nodes) * num_nodes);
	
  int redraw_needed = 0;
  while (!feof(fp)) {
	  
    char line [60]; 
    double sim_t;
    fpos_t fpos;

    if (fp == NULL)
      return 0;

    fgetpos(fp,&fpos);
    while (fgets (line, sizeof line, fp) != NULL){ 
      sscanf(line, "%lf", &sim_t);
      if (sim_t > 0.0) {
	fsetpos(fp,&fpos);
	break;
      }
      
      

      fgetpos(fp,&fpos);
    }


  }
	
  model_update(file,&model);
		
  return 0;

}
