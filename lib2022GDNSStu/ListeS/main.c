#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ndnslib/dnslib.h"

struct Data {
             int Compteur ;
	     char Message[80] ;
} ;


void list_print (sll_s * p_l)
{
int i;
int size ;

//sll_save(p_l) ;
size = sll_sizeof (p_l);
fprintf(stderr,"Taille %d \n", size ) ;

sll_first (p_l);
for (i = 0; i < size; i++)
{
if (sll_data (p_l) != NULL)
{
   struct Data *pData ;
   pData = ( struct Data *) sll_data (p_l) ;
   printf ("%d %s\n", pData->Compteur , pData->Message );
}
sll_next (p_l);
}
//sll_restore(p_l) ;
printf ("\n");
}

int main (void)
{
sll_s *p_sll = NULL;
struct Data *pData ;
int Compteur ;

Compteur = 0 ;
printf ("\t-- Initialisation --\n");
p_sll = sll_new ();
list_print (p_sll);
printf ("\n\t-- Insertion --\n");
{
int i;
for (i = 0; i < 4; i++)
{
 int taille ;
 pData = (struct Data * ) malloc( sizeof(struct Data) ) ;
 pData->Compteur=i ;
 strcpy(pData->Message,"coucou") ;
 sll_insert (p_sll, pData ) ;
 
 taille = sll_sizeof (p_sll) ;
 printf("La taille est %d\n",taille );
 //sll_first (p_sll);
}
}
list_print (p_sll);
printf ("\n\t-- Suppression -du premier élément-\n") ;
sll_first (p_sll) ;
sll_removeFirst (p_sll);
list_print (p_sll);

printf ("\n\t-- Ajout d'un élément après le premier \n") ;
pData = (struct Data * ) malloc( sizeof(struct Data) ) ;
 pData->Compteur=5 ;
 strcpy(pData->Message,"coucou 5") ;
 sll_first (p_sll) ;
 sll_insert (p_sll, pData ) ;
 list_print (p_sll);

 printf ("\n\t-- Ajout d'un élément après le dernier \n") ;
pData = (struct Data * ) malloc( sizeof(struct Data) ) ;
 pData->Compteur=6 ;
 strcpy(pData->Message,"coucou 6") ;
 sll_last (p_sll) ;
 sll_insert (p_sll, pData ) ;
 list_print (p_sll);
 
printf ("\n\t-- Destruction --\n");
sll_delete (&p_sll);

return EXIT_SUCCESS;
}

