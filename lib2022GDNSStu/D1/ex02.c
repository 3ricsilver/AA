#include "stdio.h"

main()
{
 FILE *fp ;
 char  B1[31] ,B2[31],B3[31],BB[31],BB2[31] ;//pour éviter de déborder on poura scan 30 characteres
 int d1,d2,d3 ;
 char Buffer[81] ;

 fp = fopen("ex01.c","r") ;
 while ( fgets(Buffer,sizeof Buffer,fp),!feof(fp) )//En gros on va lire une ligne qui sera stocker dans le buffer puis on continue jusqu"a la fin ou feof  check si tu as atteint la fin
 {
  printf("%s",Buffer) ;//il affiche
 }
 fclose(fp) ;
}

