#ifndef MODEL_H
#define MODEL_H

#include "opencv2/opencv.hpp"

using namespace cv;
enum _event_type {MOB, TX, RX};

typedef _event_type event_type_t;
 
struct _Node {
	int id;
	int x, y;
	event_type_t event_type
	struct _Node* sender; // if event_type == RX, it point to a valid node, otherwise NULL
};

typedef _Node Node;

Node* Node_new(int, int, int, event_type, Node*);

void model_init(FILE *,Mat *);
void model_update(FILE *,Mat *);
void model_echo(Mat *);
//
//

#endif
