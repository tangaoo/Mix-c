#include <stdio.h>
#include <unistd.h>

// 无符合整数求模 溢出是明确的
int mod_main(void)
{
    unsigned char n = 0xff;
    unsigned int  i;

    for(i = 0; i< 1000; i++)
    {
        printf("%03u ", n++);
        if(i > 31 && i % 32 == 0) printf("\n");
    }

    
}