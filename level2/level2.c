#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void p(void)
{
    uint addr;
    char buff[76];

    fflush(stdout);
    gets(buff);
    if ((addr & 0xb0000000) == 0xb0000000)
    {
        printf("(%p)\n", addr);
        _exit(1);
    }
    puts(buff);
    strdup(buff);
    return ;
}

void main(void)
{
    p();
    return ;
}
