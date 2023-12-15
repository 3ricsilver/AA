#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "protocole.h" // contient la cle et la structure d'un message


#include <sys/wait.h>



int idQ, idShm;
int fd;

PUBLICITE *PubSus=NULL;//memoire partagé



int main()
{

  MESSAGE Requete;
  Requete.requete=UPDATE_PUB;
  Requete.type=1;
  Requete.expediteur=getpid();



  // Armement des signaux

  // Masquage de SIGINT
  sigset_t mask;
  sigaddset(&mask,SIGINT);
  sigprocmask(SIG_SETMASK,&mask,NULL);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la file de messages\n",getpid());

  if((idQ = msgget(CLE,0)) == -1)
  {
    perror("Erreur de msgget");
    exit(1);
  }



  // Recuperation de l'identifiant de la mémoire partagée
  fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la mémoire partagée\n",getpid());

  if((idShm =shmget(CLE,0,0))==-1)
  {
    perror("Erreur de shmget");
    exit(1);
  }
  fprintf(stderr,"s1. %d\n",idShm);


  // Attachement à la mémoire partagée
      fprintf(stderr,"s1. %d\n",PubSus);
  // if ((PubSus = (PUBLICITE*)shmat(idShm,NULL,0)) == (PUBLICITE*)-1)
  // {
  //   fprintf(stderr,"1. %d\n",PubSus);
  //   perror("Erreur de shmat");
  //   exit(1);
  // }
  if((PubSus=(PUBLICITE*)shmat(idShm,NULL,0))==(PUBLICITE*)-1)
  {
    perror("fou");
    exit(1);
  }

  // Ouverture du fichier de publicité
  if((fd=open("publicites.dat",O_RDONLY))==-1)
  {
  return -1;
  }

  while(1)
  {
  	PUBLICITE pub;
    // Lecture d'une publicité dans le fichier
    if(read(fd,&pub,sizeof(PUBLICITE))!=sizeof(PUBLICITE))
    {
      lseek(fd, 0, SEEK_SET);
    }

    // Ecriture en mémoire partagée

    strcpy(PubSus->texte,pub.texte);
    PubSus->nbSecondes=pub.nbSecondes;//c'est pas necessaire je pense 


    // Envoi d'une requete UPDATE_PUB au serveur

    msgsnd(idQ,&Requete,sizeof(MESSAGE)-sizeof(long),0);


    //attente pub wag,er avait oublié de le mettre
    sleep(PubSus->nbSecondes);
  }
  close(fd);//normalement on arrivera jamais ici mais c'est au cas ou et je veux juste mettre un fclose 
}

