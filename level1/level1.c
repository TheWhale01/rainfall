#include <stdio.h>
#include <stdlib.h>

void run(void)
{
    fwrite("Good... Wait what?\n", 1, 0x13, stdout);
    system("/bin/bash");
    return ;
}

void main(void)
{
    char buff[76];

    gets(buff);
    return ;
}
