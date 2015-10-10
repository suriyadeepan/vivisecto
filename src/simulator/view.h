#ifndef VIEW_H
#define VIEW_H

#include "opencv2/opencv.hpp"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

#include "model.h"

using namespace cv;

/* 
 * We open with a sensor network with multitude of nodes. Actually just 10 nodes, I hate seg fault. Nodes are scattered ackwardly across the network. Let me tell you something about the network. I use the word network synonymously with the area where the sensor nodes are deployed. From a strictly programming perspective, what is a sensor node? Here we omit the "sensor" part; all we care about are that each node is mobile and has a radio capable of transmitting at a fixed power-level (for now) and receiving when within range of another node. 
 *
 * As I have mentioned in the root README.md file, the visualizer is built using the MVC pattern at its core. We have built a model that updates every instant of simulation time (sim_t), from the data ( rows in the monolithic log file events.mono) gathered from the events list (events.mono). The model is basically an array of nodes. What is a node? you mean "Node"? Yes, a "Node" is a structure with properties : id, x, y, event_type, sender_node, num_pkt_tx and num_pkt_rx. So, there you have it : your model - an array of "Node"s. 
 *
 * Let us move on to View. View handles the display, meaning it draws on to the screen, the nodes (little filled circles) in their respective position. Where do we get their locations? Yes, from the model. As we redraw the view every instant of simulation time (sim_t), the nodes change their locations, giving the viewer an illusion of moving objects (not exactly). What did we miss? the radio communication. At some instants, a number of nodes transmit, a number of nodes receive. We need to put this transmission/reception on the display. I am doing this by using transparent enough circles overlayed on the nodes. Transmission is indicated by a circle of coverage radius of the sender node. Reception is indicated by a circle of radius slightly larger than the receiver node; just large enough for the viewer to notice it. 
 *
 * For the initial testing of the view module, assume the following topology[200x200].
 * 	N1	26,73
 * 	N2  34,75
 * 	N3	89,20
 * 	N4	55,55
 * 	N5	10,90
 * 	N6	90,15
 * 	N7 	50,20
 * 	N8	75,10
 * 	N9	30,30
 * 	N10 30,10
 *
 */


//void view_x4(SIM_DIM_X,SIM_DIM_Y)
void view_xScale(Mat *,int,int);
void view_drawNodes(Mat *, Node**, int);
void view_drawRadioComm(Mat *, Node**, int);
void view_drawStats(Mat *, Node**, int,double);
void view_drawModel(Mat *, Node**, int);

extern int scale;

#endif



