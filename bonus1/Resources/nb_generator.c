#include <stdio.h>

#define INT_MIN -2147483648

int main(void)
{
    size_t stop = INT_MIN + 15;

    for (int i = INT_MIN; i <= stop; i++)
        printf("%d - %d\n", i, i * 4);
}
