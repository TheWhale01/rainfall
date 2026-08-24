#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int ac, char **av)
{
    char buff1[66];
    char buff2[66];
    FILE *fp;
    int index;

    fp = fopen("/home/user/end/.pass", "r");
    bzero(buff1, 66);
    bzero(buff2, 66);
    if (fp == NULL || ac != 2)
        return -1;
    fread(buff1, 1, 66, fp);
    buff1[65] = '\0';
    index = atoi(av[1]);
    buff1[index] = '\0';
    fread(buff2, 1, 65, fp);
    if (strcmp(buff1, av[1]) == 0)
    {
        execl("/bin/sh", "sh", (char *)NULL);
    }
    else
    {
        puts(buff2);
    }
    return 0;
}
