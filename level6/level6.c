#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return;
}

void m(void *ptr, int param2, char *param3, int param4, int param5)
{
    puts("Nope");
    return;
}

void main(int ac, char **av)
{
    char *dest;
    uint *ptr;

    dest = malloc(64);
    ptr = malloc(4);
    *ptr = m;
    strcpy(dest, av[1]);
    (*ptr)();
    return;
}
