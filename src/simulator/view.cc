#include "view.h"
#include <pthread.h>
void view_x4(Mat *view, int SIM_DIM_X, int SIM_DIM_Y){ *view = Mat(SIM_DIM_X*4, 300 + SIM_DIM_Y*4, CV_8UC4); }

void view_drawNodes(Mat *view, Node* model_node[], int node_count){ 

	for(int i=0;i<node_count;i++){

		circle( *view, Point( model_node[i]->x * 4, model_node[i]->y * 4), 15, Scalar(0,255,255), -1,8,0);
		char node_id_str[3];
		sprintf(node_id_str,"%d",i);
		putText( *view,node_id_str, Point(-6 + model_node[i]->x * 4, 6 + model_node[i]->y * 4), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(10,10,10), 2,8,false );

	}

}

void view_drawRadioComm(Mat *view, Node* model_node[], int node_count){

	for(int i=0;i<node_count;i++){

		if(model_node[i]->ev_type == 2){
			circle( *view, Point( (model_node[i]->x) * 4, (model_node[i]->y) * 4), 23, Scalar(20,255,20), -1,8,0);
			line(*view, Point(model_node[i]->x * 4,model_node[i]->y * 4),
				 	Point(model_node[model_node[i]->sender]->x*4,model_node[model_node[i]->sender]->y*4),Scalar(0,255,0), 2,8,0);
		}// if ends here

	}
}

void view_drawStats(Mat *view, Node* model_node[], int node_count, double sim_t){

	// draw simulation time on top right corner of screen
	char sim_t_str[15];
	sprintf(sim_t_str,"%lf",sim_t);	
	putText( *view,sim_t_str, Point(view->cols - 120,30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255,255,255), 2,8,false );
	
	int total_pkts_tx = 0;
	int total_pkts_rx = 0;

	for(int i=0;i<node_count;i++){
		total_pkts_tx += model_node[i]->pkts_tx;
		total_pkts_rx += model_node[i]->pkts_rx;
	}

	char stat_str[30] = "STAT";
	putText( *view,stat_str, Point(view->cols - 250,110), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
	sprintf(stat_str,"TX : %5d packets",total_pkts_tx);
	putText( *view,stat_str, Point(view->cols - 250,140), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
	sprintf(stat_str,"RX : %5d packets",total_pkts_rx);
	putText( *view,stat_str, Point(view->cols - 250,160), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

}

void view_drawModel(Mat *view, Node* model_node[], int node_count){

	char node_i_str[50] = "MODEL";
	putText( *view,node_i_str, Point(view->cols - 250,200), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

	strcpy(node_i_str,"id      x   y  pkt_tx pkt_rx");
	putText( *view,node_i_str, Point(view->cols - 250,230), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

	
	for(int i=0;i<node_count;i++){
		sprintf(node_i_str,"N%03d %3d %3d %4d %4d",i,model_node[i]->x,model_node[i]->y,model_node[i]->pkts_tx,model_node[i]->pkts_rx);
		putText( *view,node_i_str, Point(view->cols - 250,240 + ((i+1) * 20) ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
	}


}

void view_draw_nodes(Mat *view, Point *node_loc, int seed){
  /* Remove seed */
  
  (*view).setTo(cv::Scalar(0,0,0));
  for(int i=0;i<10;i++){
    circle( *view, Point( seed + node_loc[i].x * 4, seed + node_loc[i].y * 4), 20, Scalar(150,90,255), -1,8,0);
  }    
}


void threaded_view(Mat *view, Node* model_node[], int node_count){

  enum {RADIO, NODES, STATS, MODEL, MAX_VIEWS };
  pthread_t threads[MAX_VIEWS];

  typedef void* (*thread_funs)(void*);
  thread_funs *view_funcs[MAX_VIEWS];

  pthread_attr_t attr;
  
  Mat views[MAX_VIEWS](view->rows, views->cols, view->type);;
  thread_data_t data[MAX_VIEWS];
  
  for (int i = 0; i < MAX_VIEWS; i++) {
    data[i].pView = &views[i];
    data[i].nodes = model_node;
    data[i].node_count = node_count;
    data[i].node_count = node_count;
  }
  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  if (0 != pthread_create(&threads[RADIO], &attr, *view_funcs[RADIO],  &data[RADIO]))
    printf("Error: creating RADIO thread"), exit(1);
  
  
  for (int i = 0; i < MAX_VIEWS; i++) 
    if (pthread_join(threads[i], NULL) != 0)
      printf("Error joing the thread %d, exiting", i), exit(1);
  
  *view += views[RADIO];
  *view += views[NODES];
  *view += views[STATS];
  *view += views[MODEL];

  
  /*
      view_drawRadioComm(&view,nodes,node_count);
      view_drawNodes(&view,nodes,node_count);
      blur( view, view, Size( 2, 2 ) );

      view_drawStats(&view,nodes,node_count,sim_t);
      view_drawModel(&view,nodes,node_count);
      blur( view, view, Size( 3, 3 ) );
  */
}

void view_drawRadioComm_runner(void* arg){
  thread_data_t *data = (thread_data_t*) arg;  
  view_drawRadioComm((data->pView), data->nodes, data->node_count);  
  pthread_exit(NULL);
}

void view_drawNodes_runner(void* arg){
  thread_data_t *data = (thread_data_t*) arg;  
  view_drawNodes((data->pView), data->nodes, data->node_count);  
  pthread_exit(NULL);
}

void view_drawStats_runner(void* arg){
  thread_data_t *data = (thread_data_t*) arg;  
  view_drawStats((data->pView), data->nodes, data->node_count, data->sim);  
  pthread_exit(NULL);
}

void view_drawModel_runner(void* arg){
  thread_data_t *data = (thread_data_t*) arg;  
  view_drawModel((data->pView), data->nodes, data->node_count);  
  pthread_exit(NULL);
}
