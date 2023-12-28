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

#include "FichierUtilisateur.cpp"

int idQ,idSem;
//to do si semaphore a 0 enovyer dans le champs gsm et numero en attente
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
  char nom[40];

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(MODIFICATION %d) Recuperation de l'id de la file de messages\n",getpid());
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

  msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),getpid(),0);
  MESSAGE reponse={m.expediteur,getpid(),MODIF1,"","",""};

  // Lecture de la requête MODIF1
  fprintf(stderr,"(MODIFICATION %d) Lecture requete MODIF1\n",getpid());

  // Tentative de prise non bloquante du semaphore 0 (au cas où un autre utilisateut est déjà en train de modifier)
  if(semTryWait())
  {
    strcpy(reponse.data1,"KO");
    strcpy(reponse.data2,"KO");
    strcpy(reponse.texte,"KO");
    fprintf(stderr,"%s %s %s \n ",reponse.data1,reponse.data2,reponse.texte);
    msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
    exit(0);
  }

  // Connexion à la base de donnée
  MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(MODIFICATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(MODIFICATION) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

  // Recherche des infos dans la base de données
  fprintf(stderr,"(MODIFICATION %d) Consultation en BD pour --%s--\n",getpid(),m.data1);
  strcpy(nom,m.data1);
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  char requete[200];
  // sprintf(requete,...);
  sprintf(requete,"select * from UNIX_FINAL where nom like '%s';",m.data1);//a test
  mysql_query(connexion,requete);
  resultat = mysql_store_result(connexion);
  tuple = mysql_fetch_row(resultat); // user existe forcement

  // Construction et envoi de la reponse MODIF1 
  fprintf(stderr,"(MODIFICATION %d) Envoi de la reponse\n",getpid());
  strcpy(reponse.data1,"OK");
  strcpy(reponse.data2,tuple[2]);
  strcpy(reponse.texte,tuple[3]);
  fprintf(stderr,"%s %s %s \n ",reponse.data1,reponse.data2,reponse.texte);

  msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
  fprintf(stderr,"\n(%d |modif1| %d)%s %s %s\n",reponse.type,reponse.expediteur,reponse.data1,reponse.data2,reponse.texte);   

  // Attente de la requête MODIF2
  fprintf(stderr,"(MODIFICATION %d) Attente requete MODIF2...\n",getpid());
  MESSAGE Modif2;
  msgrcv(idQ,&Modif2,sizeof(MESSAGE)-sizeof(long),getpid(),0);



  // Mise à jour base de données
  fprintf(stderr,"(MODIFICATION %d) Modification en base de données pour --%s--\n",getpid(),nom);
  //sprintf(requete,...);

  sprintf(requete, "UPDATE UNIX_FINAL SET email = '%s', gsm = '%s' WHERE nom LIKE '%s';", Modif2.texte, Modif2.data2, m.data1);
  mysql_query(connexion,requete);
  //sprintf(requete,...);
  // mysql_query(connexion,requete); je pense pas que ca sera utilee vu que je le fais d'un coup

  // Mise à jour du fichier si nouveau mot de passe
  int posi;//modification mot de passe marche enfin
  posi=estPresent(m.data1);
  changeMotDePasse(posi,Modif2.data1);//ouvrir le fichier + modifier


  // Deconnexion BD
  mysql_close(connexion);

  // Libération du semaphore 0
  fprintf(stderr,"(MODIFICATION %d) Libération du sémaphore 0\n",getpid());
  semPost();
  fprintf(stderr,"\n(%d |modif2| %d)%s %s %s\n",Modif2.type,Modif2.expediteur,Modif2.data1,Modif2.data2,Modif2.texte);   

  exit(0);

}