#include<stdio.h>

extern int std_out_main(void);
extern int mod_main(void);

int main(void)
{
    printf("-------------test main\n");

    mod_main();
}