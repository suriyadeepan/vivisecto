#include "stdio.h"
#include "opencv2/opencv.hpp"

#include "simulator/helper.h"
#include "simulator/model.h"

using namespace cv;

int main(int argc, char** argv){

	static const char filename[] = "events.mono";
	FILE *file = fopen ( filename, "r" );

	if ( file != NULL ){
		char line [60]; /* or other suitable maximum line size */

		int node_id,x,y,s_node,event_type;
		double sim_t;
		Mat model;
		Mat view;
		
		/*
		while ( fgets ( line, sizeof line, file ) != NULL ){ 
			//printf("RAW > ");
			//fputs ( line, stdout ); 

			helper_vivisect(line,&sim_t,&node_id,&event_type,&x,&y,&s_node);
			model_update(&model, node_id, event_type, x, y, s_node);
			
			// view_update(&view, &model);
			// controller_action();

		}*/

		fclose ( file );
	}


	return 0;

}
