#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ndnslib/dnslib.h"

struct Zone 
{
    char nom[80];      // Nom de domaine
    char Fichier[80];  // Fichier de type db
    char DT[80];       // Champ perso 
};

void list_print(sll_s *p_sll) //affichage
{
    int size = sll_sizeof(p_sll);
    fprintf(stderr, "Taille %d \n", size);
    sll_first(p_sll);

    while (sll_data(p_sll) != NULL) 
    {
        struct Zone *pZone = (struct Zone *) sll_data(p_sll);
        printf("%s Fichier:%s %s\n", pZone->nom, pZone->Fichier, pZone->DT);
        sll_next(p_sll);
    }
    printf("\n");
}

void LectureNamedConf(char *Nom, sll_s *p_sll) //lit et extrait les infos et puis ajoute a la liste chainé
{
    FILE *file = fopen(Nom, "r");
    if (!file) 
    {
        perror("Impossible d'ouvrir le fichier.");
        return;
    }

    char line[256];
    struct Zone *pZone = NULL;
    char tempNom[80] = {0}, tempFichier[80] = {0}, tempDT[80] = {0};

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if (strstr(line, "zone") != NULL) 
        {
            pZone = (struct Zone *)malloc(sizeof(struct Zone));
            memset(pZone, 0, sizeof(struct Zone));  // Clear the structure memory
            sscanf(line, "zone \"%[^\"]\"", tempNom);
        }

        if (pZone != NULL && strstr(line, "file") != NULL) 
        {
            sscanf(line, "file \"%[^\"]\"", tempFichier);
        }

        if (pZone != NULL && strstr(line, "DT") != NULL) 
        {
            sscanf(line, "DT \"%[^\"]\";", tempDT);
        }

        if (pZone != NULL && strstr(line, "};") != NULL) 
        {
            // Copie des tampons vers le pointeur
            strcpy(pZone->nom, tempNom);
            strcpy(pZone->Fichier, tempFichier);
            strcpy(pZone->DT, tempDT);

            sll_insert(p_sll, pZone);  // Insertion dans la liste
            pZone = NULL;

            // Variables temps reset
            memset(tempNom, 0, sizeof(tempNom));  
            memset(tempFichier, 0, sizeof(tempFichier));
            memset(tempDT, 0, sizeof(tempDT));
        }
    }
    fclose(file);
}



int main() 
{
    sll_s *p_sll = sll_new();

    if (p_sll == NULL) 
    {
        fprintf(stderr, "Initialisation impossible.\n");
        return EXIT_FAILURE;
    }
    LectureNamedConf("named.conf", p_sll);
    list_print(p_sll);
    sll_delete(&p_sll);
    return EXIT_SUCCESS;
}
