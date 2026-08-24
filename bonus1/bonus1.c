#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
    char buff[40];
    int nb;

    nb = atoi(av[1]);
    if (nb < 10)
    {
        memcpy(buff, av[2], nb * 4);
        if (nb == 0x574f4c46)
        {
            execl("/bin/sh", "sh", 0);
        }
        return 0;
    }
    return 1;
}
