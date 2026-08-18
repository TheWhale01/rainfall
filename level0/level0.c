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
