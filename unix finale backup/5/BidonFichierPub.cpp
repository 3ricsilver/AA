#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "protocole.h"

int main()
{
  int fd;

  if ((fd = open("publicites.dat",O_CREAT | O_WRONLY, 0644)) == -1)
  {
    perror("Erreur de open");
    exit(1);
  }

  PUBLICITE pub[] = 
  {
    {"Lui il a eu 0/20 !",5},
    {"Avis de recherche,Pompeo dattolli pour vol de chevres !",7},
    {"Regarder Nagi no asukara UwU",4},
    {"Je suis a court de blague !",6},
    {"Vegeta est DZ !",6},
  };

  for (int i=0 ; i<4 ; i++)
  	if (write(fd,&pub[i],sizeof(PUBLICITE)) != sizeof(PUBLICITE))
  	{
  		perror("Erreur de write");
  		exit(1);
  	}
  
  close(fd);
}