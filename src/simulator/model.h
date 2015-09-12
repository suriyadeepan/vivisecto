#ifndef MODEL_H
#define MODEL_H

#include "opencv2/opencv.hpp"

using namespace cv;

void model_init(FILE *,Mat *);
void model_update(FILE *,Mat *);
void model_echo(Mat *);
//
//

#endif
