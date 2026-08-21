#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SEP " - "

void p(char *buff, char *prompt)
{
    char *ptr;
    char dest[4104];

    puts(prompt);
    read(STDIN_FILENO, dest, 4096);
    ptr = strchr(dest, '\n');
    *ptr = '\0';
    strncpy(buff, dest, 20);
    return;
}

void pp(char *buff)
{
    char first[20];
    char second[20];
    size_t len;

    p(first, SEP);
    p(second, SEP);

    strcpy(buff, first);
    len = strlen(buff);
    buff[len] = ' ';
    buff[len + 1] = 0;
    strcat(buff, second);
    return ;
}

int main(void)
{
    char buff[30];

    pp(buff);
    puts(buff);
    return 0;
}
