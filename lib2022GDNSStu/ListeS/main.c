#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dnslib.h"

struct Data {
    char Nom[80] ; // Nom de domaine
    char Fichier[80] ;  // Fichier de type db
    char MC[80] ;  // champ perso
};

void list_print (sll_s * p_l){
    int i;
    int size;

    size = sll_sizeof (p_l);
    fprintf(stderr,"\nTaille %d \n", size ) ;

    sll_first (p_l);

    for (i = 0; i < size; i++){

        if (sll_data (p_l) != NULL){
           struct Data *pData ;
           pData = ( struct Data *) sll_data (p_l) ;
           printf ("\n%s       Fichier: %s      %s\n", pData->Nom , pData->Fichier, pData->MC);
        }
        sll_next (p_l);
    }
    printf ("\n");
}

void LectureNamedConf(char *Nom, sll_s * p_sll)
{
    char B1[30], B2[30], B3[30], Buffer[50];
    FILE *fp;
    fp = fopen(Nom, "r");
    struct Data *pData ;

    while ( fgets(Buffer,sizeof Buffer,fp),!feof(fp)){
        bzero(B1,sizeof B1 ) ; bzero(B2,sizeof B2 ) ; bzero(B3,sizeof B3 ) ;
        sscanf(Buffer,"%30s %30s %30s ",B1,B2,B3) ;

        if (strcmp(B1,"zone") == 0 ){
            pData = (struct Data * ) malloc( sizeof(struct Data) ) ;
            EnleveGL(B2) ;
            printf(">Zone %s\n", B2 ) ;
            strcpy(pData->Nom,B2) ;
        }
        if (strcmp(B1,"file" ) == 0){
            EnleveGL(B2) ;
            printf(">Fichier %s\n", B2 ) ;
            strcpy(pData->Fichier,B2) ;
        }
        if (strcmp(B1,"MC" ) == 0){
            EnleveGL(B2);
            EnleveGL(B3);
            printf(">MC %s  %s\n", B2, B3) ;
            strcpy(pData->MC, B3) ;
            sll_insert(p_sll, pData ) ;
        }
        if(strcmp(B1,"zone") != 0 && strcmp(B1,"file") != 0 && strcmp(B1,"MC") != 0 )
            printf("# %s",Buffer);
    }
    fclose(fp);
}//fin fonction LectureNamedConf

int main (void){
    sll_s *p_sll = NULL;
    struct Data *pData ;
    //printf ("\t-- Initialisation --\n");
    p_sll = sll_new ();
    //printf ("\n\t-- Insertion --\n");
    LectureNamedConf("named.conf", p_sll);
    list_print (p_sll);
    //printf ("\n\t-- Destruction --\n");
    sll_delete (&p_sll);

    return EXIT_SUCCESS;
}
