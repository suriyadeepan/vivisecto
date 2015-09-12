#ifndef MODEL_H
#define MODEL_H

#include "opencv2/opencv.hpp"

using namespace cv;
 
class Node {
 public:
	int id;
	int x, y;
	int  ev_type;
	int sender; // if event_type == RX, it point to a valid node, otherwise NULL

	Node(int _id, int _x, int _y, int _ev, int _sender) {
	  id = _id;
	  x = _x; y = _y;
	  ev_type = _ev;
	  sender = _sender;
	}
};



void model_init(FILE *,Mat *);
void model_update(FILE *,Mat *);
void model_echo(Mat *);
//
//

#endif
