#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
    char filename[] = "hosts"; 
    FILE *file = fopen(filename, "r");
    char line[100];//temps
    char nom[50];//temp

    if (file == NULL) 
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return 1;
    }

    printf("Entrez un nom à rechercher : ");
    scanf("%s", nom);

    // On cherche l'adresse IP correspondant au nom donné
    while (fgets(line, sizeof(line), file))//lire jusqu'a renconter un \n
    {
        char ip[16], hostname[50];
        if (line[0] != '#' && sscanf(line, "%s %s", ip, hostname) == 2) 
        {
            if (strcmp(nom, hostname) == 0) 
            {
                printf("Adresse IP de %s : %s\n", hostname, ip);
                fclose(file);
                return 0;
            }
        }
    }

    printf("Aucune adresse IP trouvée pour le nom '%s'\n", nom);
    fclose(file);
    return 0;
}
