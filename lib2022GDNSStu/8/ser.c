/*--------------------------------------
  Herman Vanstapel
  
  ex08\ser.c 
  
  Un serveur recevant une structure 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include "../ndnslib/dnslib.h"
char * RechercheNomDomaine(char * domaine,sll_s * p);
int LectureNamedConf(char * nom,sll_s * p_sll);
void list_print (sll_s * p_l);


void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc,char *argv[])
{
 int rc ;
 int Desc ;
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 
 u_long  IpSocket ;
 u_short PortSocket ;
 
 int tm ;
 struct Requete UneRequete ;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port cli\n") ;
  exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ;
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;
 
 tm = sizeof(struct Requete) ;
 rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ;
 if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
   fprintf(stderr,"bytes reçus:%d:%s\n",rc,UneRequete.Message ) ;

    char *pchaine =NULL ;
   char Entree[80] ;
   int Octets[4] ;
   sll_s *p_sll = NULL;
   p_sll = sll_new () ;
   LectureNamedConf("./domaine/named.conf",p_sll) ;
   printf("###################################################\n") ;
   list_print(p_sll) ;
 
   if (Ipv4ToArray(Entree,Octets)!=-1)
   {
      printf("Recherche Netid %d.%d.%d\n",Octets[0],Octets[1],Octets[2]) ; 
      //pchaine= RechercheNetID(Octets, p_sll) ;
   } 
   else
   {
      char *Hote ;
      char *Domaine ;
      Hote=SepareHoteDomaine(UneRequete.Message, &Domaine) ;
      printf("Hote:%s Domaine:%s\n",Hote,Domaine) ;

      pchaine= RechercheNomDomaine(Domaine, p_sll ) ;

        if ( pchaine!=NULL )
        {
            strncpy(UneRequete.Message , pchaine, sizeof(UneRequete.Message)) ;
            printf("Trouvé\n %s\n",UneRequete.Message);

             
            printf("Type reçu %d\n", ntohl(UneRequete.Type)) ;
            /* attention l'enum peut être codé en short */
            /* reponse avec psos */
             
            UneRequete.Type = htonl(Reponse) ; 
            rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
            if ( rc == -1 )
                die("SendDatagram:") ;
            else
                fprintf(stderr,"bytes envoyés:%d\n",rc ) ;
             
            close(Desc) ;
        }
        else
        {
            strncpy(UneRequete.Message , "Rien trouve", sizeof(UneRequete.Message)) ;
            printf("%s\n",UneRequete.Message);

             
            printf("Type reçu %d\n", ntohl(UneRequete.Type)) ;
            /* attention l'enum peut être codé en short */
            /* reponse avec psos */
             
            UneRequete.Type = htonl(Reponse) ; 
            rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
            if ( rc == -1 )
                die("SendDatagram:") ;
            else
                fprintf(stderr,"bytes envoyés:%d\n",rc ) ;
             
            close(Desc) ;
        }
    }
    exit(0);
}





struct Zone
{
 char nom[80] ; // Nom de domaine
 char Fichier[80] ; // Fichier de type db
 char BR[80] ; // champ perso à remplacer par vos initiales
};





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

int LectureNamedConf(char *Named, sll_s *p_l)
{
   char B1[30] ,B2[30],B3[30],B4[30],BB[30],BB2[30] ;
   int d1,d2,d3,d4, test=0, taille;
   FILE *fp ;
   char Buffer[81], Recherche[30] ;
   struct Zone *pZone ;
   int Compteur ;
   char *position;

   printf("\nBeguin Régis et Radoux Ange\n\n");

   printf ("\t-- Initialisation --\n");
   list_print (p_l);
   printf ("\n\t-- Insertion --\n");

    fp = fopen(Named,"r") ;

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
         strcpy(pZone->BR,"Beguin Radoux") ;
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
         printf ("%s %s %s\n", pZone->nom , pZone->Fichier , pZone->BR );
      }
      sll_next (p_l);
   }
   //sll_restore(p_l) ;
   printf ("\n");
}