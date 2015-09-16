#include "map.h"

#define SIM_DIM_X  800
#define SIM_DIM_Y 1100

void map_drawGrid(Mat *map_src){

	map_src->setTo(Scalar(0,0,0));

	for(int i=0;i<map_src->rows;i+=80)
		line(*map_src, Point(0,i), Point(SIM_DIM_X,i),Scalar(30,30,30), 2,4,0);

	for(int i=0;i<=map_src->cols - 300;i+=80)
		line(*map_src, Point(i,0), Point(i,SIM_DIM_X),Scalar(30,30,30), 2,4,0);

}

