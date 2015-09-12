#include "stdio.h"

void helper_vivisect(char *line,double *sim_t,int *node_id,int *event_type,int *x,int *y,int *s_node){

	sscanf(line, "%lf %d %d %d %d %d", sim_t,node_id, event_type,x,y,s_node);
	//printf("[%lf,%d,%d,%d,%d,%d], ",*sim_t,*node_id, *event_type,*x,*y,*s_node);

}
