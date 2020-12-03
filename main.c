#include<stdio.h>

extern int std_out_main(void);
extern int mod_main(void);
int thread2_main(void);

int main(void)
{
    printf("-------------test main\n");

    thread2_main();
}