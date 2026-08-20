#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char buff[80];

void m(void *param1, int param2, char *param3, int param4, int param5)
{
    time_t time;

    time = time((time_t *)NULL);
    printf("%s - %d\n", buff, time);
}

int main(int ac, char **av)
{
    uint *ptr1;
    void *ptr2;
    uint *ptr3;
    FILE *stream;

    ptr1 = malloc(8);
    *ptr1 = 1;
    ptr2 = malloc(8);
    ptr1[1] = ptr2;
    ptr3 = malloc(8);
    *ptr3 = 2;
    ptr2 = malloc(8);
    ptr3[1] = ptr2;

    strcpy((char *)ptr1[1], av[1]);
    strcpy((char *)ptr3[1], av[2]);
    stream = fopen("/home/user/level8/.pass", "r");
    fgets(buff, 68, stream);
    puts("~~");
    return 0;
}
