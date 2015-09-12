#include "opencv2/opencv.hpp"
#include "stdio.h"

using namespace cv;


void view_x4(Mat *view, int SIM_DIM_X, int SIM_DIM_Y){ 

	*view = Mat(SIM_DIM_X*4, SIM_DIM_Y*4, CV_8UC3);

}



void view_draw_nodes(Mat *view, Point *node_loc, int seed){ /* Remove seed */

	(*view).setTo(cv::Scalar(0,0,0));
	for(int i=0;i<10;i++)
		circle( *view, Point( seed + node_loc[i].x * 4, seed + node_loc[i].y * 4), 20, Scalar(150,90,255), -1,8,0);

}


/*int main(){

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

	int seed = 0;
	while( seed < 100 ){
		view_draw_nodes(&view,node_loc,seed);
		imshow("GUI",view);
		waitKey(0);
		seed++;
	}

	waitKey(0);
	return 0;

}*/
