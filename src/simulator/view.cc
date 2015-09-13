#include "view.h"

void view_x4(Mat *view, int SIM_DIM_X, int SIM_DIM_Y){ *view = Mat(SIM_DIM_X*4, SIM_DIM_Y*4, CV_8UC3); }

void view_drawNodes(Mat *view, Point *node_loc, int seed){ /* Remove seed */

	(*view).setTo(cv::Scalar(0,0,0));

	for(int i=0;i<10;i++){
		node_loc[i].x = node_loc[i].x + seed;
		node_loc[i].y = node_loc[i].y + seed;
		circle( *view, Point( node_loc[i].x * 4, node_loc[i].y * 4), 15, Scalar(90,25,25), -1,8,0);
		char node_id_str[3];
		sprintf(node_id_str,"%d",i);
		//putText( *view,node_id_str, Point(-6 + node_loc[i].x * 4, 6 + node_loc[i].y * 4), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255,255,255), 1,8,false );
	}

}

void view_drawRadioComm(Mat *view, Point *node_loc, int seed1, int seed2){ /* Remove seed */

		circle( *view, Point( node_loc[seed1].x * 4, node_loc[seed1].y * 4), 30, Scalar(20,255,20), -1,8,0);
		line(*view, Point(node_loc[seed1].x * 4,node_loc[seed1].y * 4),
			 	Point(node_loc[seed2].x*4,node_loc[seed2].y*4),Scalar(0,255,0), 1,8,0);
}

int main(){

	srand(time(NULL));

	//node locations
	Point node_loc[10];
	node_loc[0] = Point(26,73);
	node_loc[1] = Point(34,75);
	node_loc[2] = Point(89,20);
	node_loc[3] = Point(55,55);
	node_loc[4] = Point(10,90);
	node_loc[5] = Point(90,15);
	node_loc[6] = Point(50,20);
	node_loc[7] = Point(75,10);
	node_loc[8] = Point(30,30);
	node_loc[9] = Point(30,10);

	Mat view;

	view_x4(&view,200,200);

	int seed = 1;
	while( waitKey(80) != 'q' ){
		view_drawNodes(&view,node_loc,seed);
		view_drawRadioComm(&view,node_loc,rand()%10,rand()%10);
    blur( view, view, Size( 5, 5 ) );
		imshow("GUI",view);
	}

	return 0;

}
