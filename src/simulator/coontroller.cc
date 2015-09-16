#include "controller.h"

void cntl_input(char user_ip, int *delay){

	switch(user_ip){

		case '+':
			if(*delay > 10)
				*delay -= 10;	
			else
				*delay = 1;
			break;

		case '-':
			if(*delay < 200)
				*delay += 50;
			else
				*delay = 200;
			break;

		case 'p':
			if(*delay != -1)
				*delay = -1;
			else
				*delay = 1;
			break;

		case 'n':
			*delay = -1;

	}

}
