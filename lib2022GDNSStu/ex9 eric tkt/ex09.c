#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ndnslib/dnslib.h"

const char* typeStrings[] = { "", "NS", "A", "PTR", "TD" };

// ne pas retirer le define sinon ca nique le programme -Eric le génie paresseux
#define TD (sizeof(typeStrings) / sizeof(typeStrings[0])) - 1

enum TypeIN getTypeFromString(const char* typeString) {
    for (int i = 1; i <= TD; i++) {
        if (strcmp(typeString, typeStrings[i]) == 0) {
            return (enum TypeIN)i;
        }
    }
    return NS;  // Default value if the type is not found
}


const char* enumToString(enum TypeIN type) {
    static const char* typeStrings[] = { "", "NS", "A", "PTR", "TD" };
    return typeStrings[type];
}


void listDBTD (sll_s * p_l)
{
   int i;
   int size ;

   //sll_save(p_l) ;
   size = sll_sizeof (p_l);
   fprintf(stderr,"Taille %d \n", size ) ;

   sll_first (p_l);
   for (i = 0; i < size; i++)
   {
      if (sll_data(p_l) != NULL)
      {
         struct EntreeZone *pEntreeZone ;
         pEntreeZone = ( struct EntreeZone *) sll_data (p_l) ;
         printf ("%s %d IN %s %s\n", pEntreeZone->Nom, pEntreeZone->Type, enumToString(pEntreeZone->Type) , pEntreeZone->Valeur);
      }
      sll_next (p_l);
   }
   //sll_restore(p_l) ;
   printf ("\n");
}

int LectureDBTD(char *Named, sll_s *p_l)
{
   char B1[30] ,B2[30],B3[30],B4[30],BB[30],BB2[30] ;
   int d1,d2,d3,d4, test=0, taille;
   FILE *fp ;
   char Buffer[81], Recherche[30] ;
   struct EntreeZone *pEntreeZone ;
   int Compteur ;
   char *position;

   printf("\nTruong Eric | Datolli Pompeo\n\n");

   printf ("\t-- Initialisation --\n");
   listDBTD (p_l);
   printf ("\n\t-- Insertion --\n");

    fp = fopen(Named,"r") ;

    while ( fgets(Buffer,sizeof Buffer,fp),!feof(fp) )
    {
      bzero(B1,sizeof B1 ) ; bzero(B2,sizeof B2 ) ; bzero(B3,sizeof B3 ) ; bzero(B4,sizeof B4 ) ;
      sscanf(Buffer,"%30s %30s %30s %30s",B1,B2,B3,B4) ;

      if((strcmp(B2, "IN")) == 0)
      {
         pEntreeZone = (struct EntreeZone * ) malloc( sizeof(struct EntreeZone) ) ;
         strcpy(pEntreeZone->Nom,B1) ;
         strcpy(pEntreeZone->Valeur,B4) ;
         pEntreeZone->Type = getTypeFromString(B3);
         sll_insert (p_l, pEntreeZone ) ;
         taille = sll_sizeof (p_l) ;
         printf("La taille est %d\n",taille );
         //sll_first (p_l);

         listDBTD (p_l);

         sll_last (p_l);

         
      }
            
   
    }
    fclose(fp) ;
   return EXIT_SUCCESS;
}

char *RechercheDBTD(char *Nom,int Type,sll_s * p_l)
{
   int i;
   int size ;
   struct EntreeZone *pEntreeZone ;

   //sll_save(p_l) ;
   sll_last(p_l);
   size = sll_sizeof (p_l);
   sll_first (p_l);
   for (i = 0; i < size; i++)
   {
      if (sll_data(p_l) != NULL)
      {
         
         pEntreeZone = ( struct EntreeZone *) sll_data (p_l) ;
         if(pEntreeZone->Type == Type)
         {
            if(strcmp(pEntreeZone->Nom, Nom)==0)
            {
               return(pEntreeZone->Valeur);
            } 
         }
         
      }
      sll_next (p_l);
   }
   //sll_restore(p_l) ;
   printf ("\n");
   return(NULL);
}

int main (void)
{
   char *pchaine =NULL ;
   enum TypeIN Type;
   char Entree[80] ;
   char TypeChar[5];
   int Octets[4] ;
   sll_s *p_sll = NULL;
   p_sll = sll_new () ;
   LectureDBTD("./domaine/TruongDatolli.zone",p_sll) ;
   printf("###################################################\n") ;
   listDBTD(p_sll) ;
 
   printf("------------------------------------------------\n") ;


   while(1)
   {
      printf("\n>set type=") ;
      fgets(TypeChar, sizeof(TypeChar) , stdin ) ;    
       switch (TypeChar[0]) {
           case 'A':
           case '2':
               Type = A;
               break;
           case 'N':
           case '1':
               Type = NS;
               break;
           case 'P':
           case '3':
               Type = PTR;
               break;
           case 'B':
           case '4':
               Type = TD;
               break;

       }
      printf("Le type choisi est %d", Type);
      printf("\n>") ;
      fgets(Entree, sizeof(Entree) , stdin ) ;
      Entree[strcspn(Entree, "\n")] = '\0';

      pchaine= RechercheDBTD(Entree, Type, p_sll ) ;
      
      if ( pchaine!=NULL ) 
         printf("Resultat %s\n\n",pchaine ) ;
      else
         printf("Rien trouvé !\n\n") ;
   }
   
}

