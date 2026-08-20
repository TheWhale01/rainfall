#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *auth = NULL;
char *service = NULL;

int main(void)
{
    char buf[132];

    while (1)
    {
        printf("%p, %p \n", auth, service);

        if (fgets(buf, 132, stdin) == NULL)
            return 0;

        /* Commande: "auth " */
        if (strncmp(buf, "auth ", 5) == 0)
        {
            auth = malloc(4);
            memset(auth, 0, 4);

            if (strlen(buf + 5) < 30)   // donc <= 30 octets
                strcpy(auth, buf + 5);
        }

        /* Commande: "reset" */
        if (strncmp(buf, "reset", 5) == 0)
        {
            free(auth);
            // auth n'est PAS remis à NULL
        }

        /* Commande: "service" */
        if (strncmp(buf, "service", 7) == 0)
        {
            service = strdup(buf + 7);
            // l'ancien service n'est pas free => fuite mémoire
        }

        /* Commande: "login" */
        if (strncmp(buf, "login", 5) == 0)
        {
            if (*(int *)(auth + 32) == NULL)
            {
                fwrite("Password:\n", 1, 10, stdout);
            }
            else
            {
                system("/bin/sh");
            }
        }
    }
}
