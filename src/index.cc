#include "index.h"
#include "math.h"

int index_index(char* filename){

	FILE *mfp = fopen ( filename, "r" );
	FILE *ifp = fopen ( "events.index", "w" );

	fpos_t fpos;
	char fpos_str[8];
	double sim_t = 0.0;
	double sim_t_prev = 0.0;
	int num_lines = 0;
	char line[50];

	if (mfp == NULL || ifp == NULL)
		return -1;

	fgetpos(mfp,&fpos);
	sprintf(fpos_str,"%d\n",fpos);
	fputs(fpos_str, ifp);
	num_lines++;

	while (fgets (line, sizeof line, mfp) != NULL){ 

		sscanf(line, "%lf", &sim_t);

		if (ceil(sim_t) == sim_t && sim_t > sim_t_prev){
			sprintf(fpos_str,"%d\n",fpos);
			fputs(fpos_str, ifp);
			num_lines++;
		}

		sim_t_prev = sim_t;
		fgetpos(mfp,&fpos);
	}

	fclose(mfp);
	fclose(ifp);

	return num_lines;
}


