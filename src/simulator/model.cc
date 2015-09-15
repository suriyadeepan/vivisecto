#include "model.h"
#include "stdio.h"

Node* Node_new(int _id, int _x, int _y, int _ev, int _sender) {
  Node * pnode = (Node*)malloc(sizeof(*pnode));
  
  if (pnode == NULL)
    return NULL;

  pnode->id = _id;
  pnode-> x = _x; 
  pnode->y = _y;
  pnode->ev_type = _ev;
  pnode->sender = _sender;
  pnode->pkts_tx = pnode->pkts_rx = 0;
  return pnode;
}

void Node_print(Node* p){
  if (p != NULL)
    printf("%d\t(%d,%d)\t%d\t%d\n",p->id, p->x, p->y, p->ev_type, p->sender  ? p->sender : -1);
}

int model_init(FILE *fp){

  int node_count = 0;
  char line [60]; 
  double sim_t;
  fpos_t fpos;

  if (fp == NULL)
    return 0;

  fgetpos(fp,&fpos);
  while (fgets (line, sizeof line, fp) != NULL){ 
    sscanf(line, "%lf", &sim_t);
    if (sim_t > 0.0) {
      fsetpos(fp,&fpos);
      break;
    }
      
    node_count++;
    //fgetpos(fp,&fpos);
  }
  
  //printf("\nNum Nodes : %d\n",node_count);
  return node_count;
}

void model_update(FILE *fp, Mat *model){
  char line [60]; 
  double sim_t;
  fpos_t fpos;

  if (fp == NULL)
    return;

  fgetpos(fp,&fpos);
  while (fgets (line, sizeof line, fp) != NULL){ 
    sscanf(line, "%lf", &sim_t);
    if (sim_t > 0.0) {
      fsetpos(fp,&fpos);
      break;
    }
      
    //node_count++;
    fgetpos(fp,&fpos);
  }
  
}

void Model_print(Node* nodes[],int node_count){

	for(int i=0;i<node_count;i++)
		Node_print(nodes[i]);

}


void model_seek(FILE *fp, FILE *ifp, int sim_seek_time){

	fpos_t target_fpos;
	int line_num = 0;
  char line [60]; 
	
	// BUG FIX : set position of *ifp to 0
	fseek(ifp,0,SEEK_SET);

	while(fgets (line, sizeof line, ifp) != NULL){

		if(line_num == sim_seek_time){
			sscanf(line,"%d",&target_fpos);
			break;
		}
		line_num++;
	}

	// now that we know where we should jump, let us jump there
	fsetpos(fp,&target_fpos);	
	
}

