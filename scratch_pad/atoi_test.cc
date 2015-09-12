#include "stdio.h"
#include "stdlib.h"

int main(){

	char line[] = "1.453245435 0 0 52 36 -1";

	//char str[] = "12345.56";
	long double sim_t;
	int node_id,event_type,x,y,s_node;

	sscanf(line, "%lf %d %d %d %d %d", &sim_t,&node_id, &event_type,&x,&y,&s_node);

	printf("\nsim_t : %lf",sim_t);
	printf("\nnode_id: %d",node_id);
	printf("\nx,y : (%d,%d)",x,y);
	printf("\nevent_type : %d",event_type);
	printf("\ns_node : %d",s_node);

	return 0;

}
