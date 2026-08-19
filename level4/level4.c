#include <stdio.h>
#include <stdlib.h>

uint m;

void p(char *buff)
{
    printf(buff);
    return;
}

void n(void)
{
    char buff[520];

    fgets(buff, 512, stdin);
    p(buff);
    if (m == 16930116)
    {
        system("/bin/cat /home/user/level5/.pass");
    }
    return;
}

void main(void)
{
    n();
    return;
}
