# Level 0

La commande `ls -la` nous donne ce resultat:

```bash
dr-xr-x---+ 1 level0 level0     60 Mar  6  2016 .
dr-x--x--x  1 root   root      340 Sep 23  2015 ..
-rw-r--r--  1 level0 level0    220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level0 level0   3530 Sep 23  2015 .bashrc
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
-rw-r--r--  1 level0 level0    675 Apr  3  2012 .profile
```

Apres avoir telecharge et passe dans Ghidra le binaire `level0` nous optenons plus ou moins ce code C:

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av)
{
    int nb;
    char *cmd;
    uid_t uid;
    gid_t gid;

    nb = atoi(av[1]);
    if (nb == 423)
    {
        cmd = strdup("/bin/sh");
        gid = getegid();
        uid = geteuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        execv("/bin/sh", &cmd);
    }
    else
    {
        fwrite("No !\n", 1, 5, (FILE *)stderr);
    }
    return 0;
}
```

Il faut donc executer le programme avec 423 comme argument pour executer le shell avec level1 (Cf. permissions de fichier)

Ensuite nous pouvons donc recuperer le flag:

```bash
cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
