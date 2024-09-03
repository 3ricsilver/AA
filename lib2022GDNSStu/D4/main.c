#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ndnslib/dnslib.h"

struct Zone 
{
   char nom[80];
   char fichier[80];
   char DT[80];
};


void list_print (sll_s * p_l)
{
   int i;
   int size;

   size = c(p_l);
   fprintf(stderr,"Taille %d \n", size);

   sll_first (p_l);
   for (i = 0; i < size; i++)
   {
      if (sll_data(p_l) != NULL) // Si la donnée existe
      {
         struct Zone *pZone;
         pZone = (struct Zone*) sll_data (p_l);
         printf ("%s | %s | %s\n", pZone->nom , pZone->fichier, pZone->DT);
      }
      sll_next (p_l); // On passe au suivant
   }
   printf("\n");
}

int main (void)
{
   sll_s *p_sll = NULL;
   struct Zone *pZone;
   int Compteur = 0;

   printf ("\t-- Initialisation --\n");
   p_sll = sll_new();
   list_print(p_sll); // Affichage de la liste

   printf ("\n\t-- Insertion --\n");

   int taille;
   pZone = (struct Zone*) malloc(sizeof(struct Zone)); // Alloc dynamique d'une taille de la struct Zone
   strcpy(pZone->nom, "world.cosmos");
   strcpy(pZone->fichier,"Fichier : world.zone");
   strcpy(pZone->DT, "Dattoli Truong");

   sll_insert(p_sll, pZone); // Insertion dans la liste
    
   taille = sll_sizeof(p_sll); // Récupération de la taille
   printf("La taille est %d\n",taille);
   
   list_print(p_sll);

   sll_last (p_sll);
   pZone = (struct Zone * ) malloc( sizeof(struct Zone) );
   strcpy(pZone->nom,"113.112.111.in-addr.arpa");
   strcpy(pZone->fichier,"Fichier : 111.112.113.zone");
   strcpy(pZone->DT,"Dattoli Truong") ;
   sll_insert (p_sll, pZone );
   taille = sll_sizeof (p_sll);
   printf("La taille est %d\n",taille );

   list_print (p_sll);

   return EXIT_SUCCESS;
}

