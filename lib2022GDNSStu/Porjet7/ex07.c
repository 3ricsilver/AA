#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ndnslib/dnslib.h"

struct Zone
{
 char nom[80] ; // Nom de domaine
 char Fichier[80] ; // Fichier de type db
 char TD[80] ; // champ perso
};

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
      if (sll_data(p_l) != NULL)
      {
         struct Zone *pZone ;
         pZone = ( struct Zone *) sll_data (p_l) ;
         printf ("%s %s %s\n", pZone->nom , pZone->Fichier , pZone->TD );
      }
      sll_next (p_l);
   }
   //sll_restore(p_l) ;
   printf ("\n");
}

/*      
    sll_sizeof(p_l) : Récupère la taille de la liste.
    sll_first(p_l) : Fixe le pointeur de liste sur le premier élément.
    sll_data(p_l) : Récupère les données à la position actuelle de la liste.
    sll_next(p_l) : Permet de passer à l'élément suivant de la liste.

    list_print : pour afficher
*/

int LectureNamedConf(char *Named, sll_s *p_l)
{
   char B1[30] ,B2[30],B3[30],B4[30],BB[30],BB2[30] ;
   int d1,d2,d3,d4, test=0, taille;
   FILE *fp ;
   char Buffer[81], Recherche[30] ;
   struct Zone *pZone ;
   int Compteur ;
   char *position;

   printf("\nTruong Eric et Pompeo Datolli\n\n");

   printf ("\t-- Initialisation --\n");
   list_print (p_l);
   printf ("\n\t-- Insertion --\n");

    fp = fopen(Named,"r") ;
    if(!fp)
    {
      printf("errreur ficher introuvable");
      return 0;
    }

    while ( fgets(Buffer,sizeof Buffer,fp),!feof(fp) )
    {
      bzero(B1,sizeof B1 ) ; bzero(B2,sizeof B2 ) ; bzero(B3,sizeof B3 ) ; bzero(B4,sizeof B4 ) ;
      sscanf(Buffer,"%30s %30s %30s %30s",B1,B2,B3,B4) ;

      if((strcmp(B1, "zone")) == 0)
      {
         strncpy(B2, &B2[1], strlen(B2));
         B2[strlen(B2)-1] = '\0';
         pZone = (struct Zone * ) malloc( sizeof(struct Zone) ) ;
         strcpy(pZone->nom,B2) ;
      }
      if((strcmp(B1, "file")) == 0)
      {
         strncpy(B2, &B2[1], strlen(B2));
         B2[strlen(B2)-2] = '\0';
         strcpy(pZone->Fichier,B2) ;
         strcpy(pZone->TD,"Truong Datolli") ;
         sll_insert (p_l, pZone ) ;
         taille = sll_sizeof (p_l) ;
         printf("La taille est %d\n",taille );
         //sll_first (p_l);

         list_print (p_l);

         sll_last (p_l);

         
      }
            
   
    }
    fclose(fp) ;
   return EXIT_SUCCESS;
}

/*    
         LectureNamedConf : Lit un fichier de configuration named et remplit la liste chaînée p_l avec les structures de la zone.
        Ouvre le fichier spécifié par Named pour lecture.
        Lit chaque ligne et l'analyse en B1, B2, B3 et B4.
        Si une ligne "zone" est trouvée, une structure Zone est initialisée.
        Si une ligne "file" est trouvée, il complète la structure Zone, affecte le champ personnalisé et l'insère dans la liste.
        */

char* RechercheNomDomaine(char *Domaine, sll_s * p_l)
{
   int i;
   int size ;
   struct Zone *pZone ;

   //sll_save(p_l) ;
   sll_last(p_l);
   size = sll_sizeof (p_l);
   sll_first (p_l);
   for (i = 0; i < size; i++)
   {
      if (sll_data(p_l) != NULL)
      {
         
         pZone = ( struct Zone *) sll_data (p_l) ;
         if(strcmp(pZone->nom, Domaine)==0)
         {
            printf("Domaine #%s# zone #%s#\n", pZone->nom, pZone->Fichier);
            return(pZone->Fichier);
         } 
      }
      sll_next (p_l);
   }
   //sll_restore(p_l) ;
   printf ("\n");
   return(NULL);
}

//RechercheNomDomaine : Recherche un nom de domaine dans la liste chaînée et renvoie le nom du fichier associé s'il est trouvé.

int main (void)
{
   char *pchaine =NULL ;
   char Entree[80] ;
   int Octets[4] ;
   sll_s *p_sll = NULL;
   p_sll = sll_new () ;
   LectureNamedConf("./domaine/named.conf",p_sll) ;//on va lire le contenu de named conf et le mettre dans la liste chainé
   printf("###################################################\n") ;
   list_print(p_sll) ;//afficher
 
   printf("------------------------------------------------\n") ;
   printf("\nEntrez une ip ou un nom de domaine : ") ;//la j'entre un nom de domaine
   fgets(Entree, sizeof(Entree) , stdin ) ;
   Enleve1013(Entree) ;
   fprintf(stderr,"#%s#\n",Entree) ;
   if (Ipv4ToArray(Entree,Octets)!=-1)
   {
      printf("Recherche Netid %d.%d.%d\n",Octets[0],Octets[1],Octets[2]) ; 
      //pchaine= RechercheNetID(Octets, p_sll) ;
   } 
   else
   {
      char *Hote ;
      char *Domaine ;
      Hote=SepareHoteDomaine(Entree, &Domaine) ;
      printf("Hote:%s Domaine:%s\n",Hote,Domaine) ;
      pchaine= RechercheNomDomaine(Domaine, p_sll ) ;
   } 
   if ( pchaine!=NULL ) 
      printf("Resultat %s\n\n",pchaine ) ;
   else
      printf("Rien trouvé !\n\n") ;
}

