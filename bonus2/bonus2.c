#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define FI "fi"
#define NL "nl"

int language = 0;

typedef struct {
    char buff1[40];
    char buff2[36];
} user_t;

void greetuser(user_t user)
{
    char greet[72];

    if (language == 1)
        strcpy(greet, "Hyvää päivää ");
    else if (language == 2)
        strcpy(greet, "Goedemiddag! ");
    else if (language == 0)
        strcpy(greet, "Hello ");
    strcat(greet, (char*)&user);
    puts(greet);
    return;
}

int main(int ac, char **av)
{
    user_t user;
    char *lang;

    if (ac != 3)
        return 1;
    bzero(&user, 76);
    strncpy(user.buff1, av[1], 40);
    strncpy(user.buff2, av[2], 32);
    lang = getenv("LANG");
    if (lang != NULL)
    {
        if (memcmp(lang, FI, 2) == 0)
        {
            language = 1;
        }
        else if (memcmp(lang, NL, 2) == 0)
        {
            language = 2;
        }
    }
    greetuser(user);
    return 0;
}
