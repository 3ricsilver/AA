
#include <stdio.h>
#include <string.h>

main()
{
 char  B1[31] ,B2[31],B3[31],BB[31],BB2[31] ;//pour éviter de déborder on poura scan 30 characteres
 int d1,d2,d3 ;

 char *Buffer = "primary    249.249.192.in-addr.arpa     db.192.249.249" ;
 char *Buffer2="249.192.in-addr.arpa" ;//on veut recupéerer les  valeurs du réseau pour parser les chaines de characteres

 bzero(B1,sizeof B1 ) ; bzero(B1,sizeof B2 ) ; bzero(B1,sizeof B3 ) ;//tj mettre les buffer a zero bzero le fait automatiquement
 sscanf(Buffer,"%30s  %30s ",B1,B2) ;//protection pour pas qu'on déborde |on aura 249.192.in-addr.arpa dans B2
 printf("T1 %s  %s \n",B1,B2) ;
 bzero(B1,sizeof B1 ) ; bzero(B1,sizeof B2 ) ; bzero(B1,sizeof B3 ) ;
 sscanf(Buffer,"%30s  %30s  %30s",B1,B2,B3) ;
 printf("T2 %s  %s  %s \n",B1,B2,B3) ;
 sscanf(B2,"%d.%d.%d.%30s",&d1,&d2,&d3,BB) ;//on va parser le buffer 2 || on va avoir dans D1 249 248 192
 printf(" %d %d %d %s\n",d1,d2,d3,BB) ;

 d1 = d2 = d3 = 0 ;
 sscanf(Buffer2,"%d.%d.%d.%30s",&d1,&d2,&d3,B3) ;
 printf(" %d %d %d %s\n",d1,d2,d3,BB) ;
 
 sscanf(Buffer2,"%d.%d.%30s",&d1,&d2,B3) ;
 printf(" %d %d %s\n",d1,d2,BB) ;
}


//eric en gros pense a cin ca prends pas les espaces
//mon reuf tu fais peur