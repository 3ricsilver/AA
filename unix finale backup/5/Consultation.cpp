#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <mysql.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ,idSem;
//probablement foireux
struct sembuf operations[2];

int semWait()
{
  struct sembuf op={0,-1,SEM_UNDO};
  return semop(idSem,&op,1);//1 =nbr d'operation petit eric du futur
}

int semTryWait()
{
  struct sembuf op={0,-1,SEM_UNDO | IPC_NOWAIT};
  return semop(idSem,&op,1);//1 =nbr d'operation petit eric du futur

}
void semPost()
{
  struct sembuf op={0,1,SEM_UNDO};
  semop(idSem,&op,1);//1 =nbr d'operation petit eric du futur
}


int main()
{
  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CONSULTATION %d) Recuperation de l'id de la file de messages\n",getpid());

  if((idQ = msgget(CLE,0)) == -1)
  {
    perror("Erreur de msgget");
    exit(1);
  }

  // Recuperation de l'identifiant du sémaphore

  if ((idSem = semget(CLE,0,0)) == -1)
  {
    perror("Erreur de semget");
    exit(1);
  }


  MESSAGE m;
  MESSAGE consultation;
  msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0);
  fprintf(stderr, "(CONSULTATION %d) Lecture requete CONSULT\n", getpid());

  // Tentative de prise bloquante du semaphore 0
  fprintf(stderr,"(CONSULTATION %d) Prise bloquante du sémaphore 0\n",getpid());
    
  //je ne sais pas si le prof acceptera mais c'est la seul maniere viable que je vois pour mettre en attendre

  
  semWait();
  



  // Connexion à la base de donnée
  MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(CONSULTATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(CONSULTATION) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

  // Recherche des infos dans la base de données
  fprintf(stderr,"(CONSULTATION %d) Consultation en BD (%s)\n",getpid(),m.data1);
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  char requete[200];

  sprintf(requete,"select * from UNIX_FINAL where nom like '%s';",m.data1);
  mysql_query(connexion,requete),
  resultat = mysql_store_result(connexion);
  if ((tuple = mysql_fetch_row(resultat)) != NULL)
  {
    strcpy(consultation.data1,"OK");
    strcpy(consultation.data2,tuple[2]);
    strcpy(consultation.texte,tuple[3]);
  }
  else
  {
    strcpy(consultation.data1,"KO");
  }
    // Construction et envoi de la reponse


    consultation.type=m.expediteur;
    consultation.expediteur=getpid();
    consultation.requete=CONSULT;


    msgsnd(idQ,&consultation,sizeof(MESSAGE) - sizeof(long), 0);
    kill(consultation.type,SIGUSR1);


    // Deconnexion BD
    mysql_close(connexion);
  
  // Libération du semaphore 0
  fprintf(stderr,"(CONSULTATION %d) Libération du sémaphore 0\n",getpid());
  semPost();


    fprintf(stderr,"\n(%d |2| %d)%s %s\n",m.type,m.expediteur,m.data1,m.data2);   
        fprintf(stderr,"\n(%d |2| %d)%s %s\n",m.type,m.expediteur,m.data1,m.data2);   


  exit(0);
}