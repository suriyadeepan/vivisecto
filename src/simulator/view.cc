#include "view.h"

void view_x4(Mat *view, int SIM_DIM_X, int SIM_DIM_Y){ *view = Mat(SIM_DIM_X*4, SIM_DIM_Y*4, CV_8UC4); }

void view_drawNodes(Mat *view, Node* model_node[], int node_count,double sim_t){ 

	// draw simulation time on top right corner of screen
	char sim_t_str[15];
	sprintf(sim_t_str,"%lf",sim_t);	
	putText( *view,sim_t_str, Point(view->cols - 120,30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255,255,255), 2,8,false );
	
	for(int i=0;i<node_count;i++){

		circle( *view, Point( model_node[i]->x * 4, model_node[i]->y * 4), 15, Scalar(0,255,255), -1,8,0);
		char node_id_str[3];
		sprintf(node_id_str,"%d",i);
		putText( *view,node_id_str, Point(-6 + model_node[i]->x * 4, 6 + model_node[i]->y * 4), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(10,10,10), 2,8,false );

	}

}

void view_drawRadioComm(Mat *view, Node* model_node[], int node_count){

	view->setTo(cv::Scalar(0,0,0));

	for(int i=0;i<node_count;i++){

		if(model_node[i]->ev_type == 2){
			circle( *view, Point( (model_node[i]->x) * 4, (model_node[i]->y) * 4), 23, Scalar(20,255,20), -1,8,0);
			line(*view, Point(model_node[i]->x * 4,model_node[i]->y * 4),
				 	Point(model_node[model_node[i]->sender]->x*4,model_node[model_node[i]->sender]->y*4),Scalar(0,255,0), 2,8,0);
		}// if ends here

		// Transmitting node
		else if(model_node[i]->ev_type == 1)
			circle( *view, Point( (model_node[i]->x) * 4, (model_node[i]->y) * 4), 21, Scalar(255,191,0), -1,8,0);

	}// end of FOR

}
