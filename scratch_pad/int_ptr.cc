#include "stdio.h"
#include "stdlib.h"

void func(int *x){ *x = 89; }

int main(){

	int var = 35;

	printf("\n%x",&var);
	printf("\n%d",var);

	func(&var);

	printf("\n%x",&var);
	printf("\n%d",var);
	
	return 0;

}
