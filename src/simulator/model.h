#ifndef MODEL_H
#define MODEL_H

#include "opencv2/opencv.hpp"

using namespace cv;
 
typedef struct _Node {
  int id;
  int x, y;
  int  ev_type;
  int sender; // if event_type == RX, it point to a valid node, otherwise NULL
  int pkts_tx;
  int pkts_rx;
} Node;

int model_init(FILE *);
void model_update(FILE *);
//void model_echo(Mat *);
//
//
Node* Node_new(int,int,int,int,int );
void Node_print(Node *);
void Model_print(Node**,int);

void model_seek(FILE*,FILE*,int);
#endif
