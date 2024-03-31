//en gros tapper un nom et puis retourner l'ip
//le prof a fait le lengh

#include <stdio.h>
#include <string.h>


main()
{
	FILE *fp ;
	char Buffer[81] ;

	fp = fopen(".c","r") ;
	while ( fgets(Buffer,sizeof Buffer,fp),!feof(fp) )//feof test fin de lecture(only read)
	{
		printf("%s",Buffer) ;
	}
	fclose(fp) ;
}
