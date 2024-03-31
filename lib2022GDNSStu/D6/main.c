#include <stdio.h>
#include <stdlib.h>
#include "../ndnslib/dnslib.h"


int main (void)
{
  char  *pchaine =NULL ;
  char  Entree[80] ;
  int Octets[4] ;
  // sll_s *p_sll = NULL;
  // p_sll = sll_new () ;
  // LectureNamedConf("named.conf",p_sll) ;
  printf("\n") ;
  
  printf("------------------------------------------------\n") ;
  printf("Entrez une ip ou un nom de domaine;") ;
  fgets(Entree, sizeof(Entree) , stdin ) ;
  Enleve1013(Entree) ;
  fprintf(stderr,"#%s#\n",Entree) ;
  if (Ipv4ToArray(Entree,Octets)!=-1)
  {
     printf("Recherche Netid %d.%d.%d\n",Octets[0],Octets[1],Octets[2]) ;   
     // pchaine= RechercheNetID(Octets, p_sll) ;
  }  
  else
  {
      char *Hote ;
      char *Domaine ;
      Hote=SepareHoteDomaine(Entree, &Domaine) ;
      printf("Hote:%s Domaine:%s\n",Hote,Domaine) ;
      // pchaine= RechercheNomDomaine(Domaine, p_sll ) ;
  }    
  if ( pchaine!=NULL ) 
     printf(" Resultat %s\n",pchaine ) ;
  else
     printf("Rien trouvé !\n") ;
}
