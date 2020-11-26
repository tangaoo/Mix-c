#include <stdio.h>
#include <stdlib.h>

int system_main(void)
{
	printf("Runing ps\n");	
	system("ps ax&");
	printf("Done\n");

	exit(0);
}
