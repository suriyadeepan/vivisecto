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
int add_to_array(Node* list[], int len, char* string){
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
	FILE *file = fopen ( filename, "r" );

	// initiate model
	Mat model;

	int num_nodes = model_init(file,&model);
	nodes = (Node**)malloc(sizeof (*nodes) * num_nodes);
	
	while (!feof(fp)) {
	  
	}
	
	model_update(file,&model);
		
	return 0;

}
