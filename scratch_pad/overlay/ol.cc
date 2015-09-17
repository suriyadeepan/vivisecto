#include "stdio.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char* argv[]){

	Mat bigImage = imread(argv[1]);
	Mat smallImage = imread(argv[2]);


	Rect roi( Point( 0, 0 ), Size( 350,350) );

	smallImage = smallImage(roi);

	Mat destinationROI = bigImage( roi );
	smallImage.copyTo( destinationROI );

	imshow("im",destinationROI);
	waitKey(-1);


	return 0;
}
