#include "stdio.h"
#include "opencv2/opencv.hpp"

#include "simulator/helper.h"
#include "simulator/model.h"

using namespace cv;

int main(int argc, char** argv){

	static const char filename[] = "events.mono";
	FILE *file = fopen ( filename, "r" );

	// initiate model
	Mat model;

	model_init(file,&model);

	model_update(file,&model);
		
	return 0;

}
