#include "model.h"
#include "stdio.h"

void model_init(FILE *fp, Mat *model){

	int node_count = 0;

	if ( fp != NULL ){

		char line [60]; 
		double sim_t;
		fpos_t fpos;
		fgetpos(fp,&fpos);

		while ( fgets ( line, sizeof line, fp ) != NULL ){ 

			sscanf(line, "%lf", &sim_t);

			if( sim_t > 0.0 ){
				fsetpos(fp,&fpos);
				break;
			}

			node_count++;

			fgetpos(fp,&fpos);
		}
	}

 	*model = Mat(4,node_count, CV_8UC1); 
	//printf("\nNum Nodes : %d\n",node_count);

}

void model_update(FILE *fp, Mat *model){

	// thevayatra variables
	int node_id;
	int x,y;
	int event_type;
	int s_node;

	if ( fp != NULL ){

		char line [60]; 
		double sim_t, sim_curr_t;
		fpos_t fpos;
		fgetpos(fp,&fpos);

		while ( fgets ( line, sizeof line, fp ) != NULL ){ 

			sscanf(line, "%lf %d %d %d %d %d", &sim_t,&node_id,&event_type,&x,&y,&s_node);

			if( sim_t > sim_curr_t ){
				fsetpos(fp,&fpos);
				break;
			}

			sim_curr_t = sim_t;
			fgetpos(fp,&fpos);

			// separate the values in line
			// update the model with values in line
			(*model).at<int>(node_id,0) = x;
			(*model).at<int>(node_id,1) = y;
			if(event_type == 1){
				(*model).at<int>(node_id,2) = 1;
				(*model).at<int>(node_id,3) = 0;
			}
			else if(event_type == 2){
				(*model).at<int>(node_id,2) = 0;
				(*model).at<int>(node_id,3) = s_node;
			}
			else{
				(*model).at<int>(node_id,2) = 0;
				(*model).at<int>(node_id,3) = 0;
			}

		}// end of while

	}// end of if

	model_echo(model);
	
	
}

void model_echo(Mat *model){

	int dim_x = model->rows;
	int dim_y = model->cols;

	for(int i = 0; i<dim_x;i++){
		printf("\n");
		for(int j=0; j<dim_y;j++){
			printf("%d ",(*model).at<int>(i,j));
		}

	}
	

}

