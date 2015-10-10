#include "map.h"

void map_drawGrid(Mat *map_src){

	int SIM_DIM_X = scale * 200;
	int SIM_DIM_Y = SIM_DIM_X + 300;

	map_src->setTo(Scalar(0,0,0));

	for(int i=0;i<map_src->rows;i+=80)
		line(*map_src, Point(0,i), Point(SIM_DIM_X,i),Scalar(30,30,30), 2,4,0);

	for(int i=0;i<=map_src->cols - 300;i+=80)
		line(*map_src, Point(i,0), Point(i,SIM_DIM_X),Scalar(30,30,30), 2,4,0);

}

