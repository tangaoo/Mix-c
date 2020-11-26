#include <stdio.h>

char* static_mem(void)
{
	static char str[10] = "hi";

	return str; 
}

int hello_main()
{
	printf("1, %p, %s\n", static_mem(), static_mem());
	printf("2, %p, %s\n", static_mem(), static_mem());

	return 0;
}
