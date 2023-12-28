#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <mysql.h>
#include <setjmp.h>
#include "protocole.h" // contient la cle et la structure d'un message

#include "FichierUtilisateur.h"

#include <mysql.h>//truc de la théorie pour add les tupples 

#include <setjmp.h>
int idQ,idShm,idSem;
TAB_CONNEXIONS *tab;

////4////
int PubliciteFils;


int ShID; //pour la memoire partagé valeur clé
//////////

sigjmp_buf flag;//tampon pour se souvenir d'ou jump



void afficheTab();

MYSQL* connexion;
/////1.3/////////////////////
void HandlerSIGINT(int sig);
/////////////////////////////
void HandlerSIGCHLD(int sig);

union semun
{
int val;
struct semid_ds *buf;
unsigned short *array;
} arg;


int main()
{

  /*////////ARMEMEMENT////// */

  ////1.3///////////////// c le truc qui permet de ctrl +c 
  struct sigaction dz;//on arme un signal pour qu'il ignore
  dz.sa_handler = HandlerSIGINT;//int sig n'est pas utilisé et correspond au numero du signal
  sigemptyset(&dz.sa_mask);
  dz.sa_flags = 0;
  sigaction(SIGINT,&dz,NULL);
  // ::::::::::::::::::::::::: c le truc qui vva s'occuper de ses fils zombie via wait qui va juste attendre leurs morts tkt

  struct sigaction eric;//on arme un signal pour qu'il ignore
  eric.sa_handler = HandlerSIGCHLD;//int sig n'est pas utilisé et correspond au numero du signal
  sigemptyset(&eric.sa_mask);
  eric.sa_flags = 0;
  
  sigaction(SIGCHLD,&eric,NULL);

  /////////////////////////////////
  //Semaphore // a test
  if ((idSem = semget(CLE,1,IPC_CREAT | IPC_EXCL | 0600)) == -1)//probablement va devoir changer le nombre de semaphore a qlq chose plus grrand que 1
  {
    perror("Erreur de semget");
    exit(1);
  }
  semctl(idSem,0,SETVAL,1);//initie numero 0 a 1






  ////////////////////////////////



  // Connection à la BD
  connexion = mysql_init(NULL);
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(SERVEUR) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

  // Armement des signaux
  //to do a faire eric futur
  // Creation des ressources
  fprintf(stderr,"(SERVEUR %d) Creation de la file de messages\n",getpid());
  if ((idQ = msgget(CLE,IPC_CREAT | IPC_EXCL | 0600)) == -1)  // CLE definie dans protocole.h
  {
    perror("(SERVEUR) Erreur de msgget");
    exit(1);
  }



  //////////4////////////////////
  //creer !! verif si pas déja créer !!! les perms pour faire de la memoire partagé  pour ecrire et lire seulement pour le proprio
  //Création de memoire partagé//
  ShID=shmget(CLE,200,IPC_CREAT | IPC_EXCL | 0600);//on crée la mémoire partager
//to do erric du futur shmget c'est pour recup la memoire partagé shmget(CLE,200,);le dernier pour savoir si c'est pour recupérer ou en créer une ou 0

  //////////////////////////////

  // Initialisation du tableau de connexions
  fprintf(stderr,"(SERVEUR %d) Initialisation de la table des connexions\n",getpid());
  tab = (TAB_CONNEXIONS*) malloc(sizeof(TAB_CONNEXIONS)); 

  for (int i=0 ; i<6 ; i++)
  {
    tab->connexions[i].pidFenetre = 0;
    strcpy(tab->connexions[i].nom,"");
    for (int j=0 ; j<5 ; j++) tab->connexions[i].autres[j] = 0;
      tab->connexions[i].pidModification = 0;
  }
  tab->pidServeur1 = getpid();
  tab->pidServeur2 = 0;
  tab->pidAdmin = 0;
  tab->pidPublicite = 0;

  afficheTab();



  ////////4/////////
  //création fils
   PubliciteFils=fork();


  // Creation du processus Publicite 
  if(PubliciteFils==0)
  {
    execl("./Publicite","Publicite",(char*)NULL);//j'ai vraiment besoin de t'expliquer eric du futur ?
  }
  

  /////////////////
  int i,k,j,VariableTemp,i2,i3;
  MESSAGE m;
  MESSAGE reponse;
  char requete[200];
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  PUBLICITE pub;



  int ret;


  while(1)
  {
    if ((ret = sigsetjmp(flag,1)) != 0)
    {
      printf("\nRetour du saut %d...\n",ret);
    }


  	fprintf(stderr,"(SERVEUR %d) Attente d'une requete...\n",getpid());
    if (msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),1,0) == -1)
    {
      perror("(SERVEUR) Erreur de msgrcv"); //ca crash ici depuis l'introduction du sigchid
      msgctl(idQ,IPC_RMID,NULL);
      exit(1);
    }

    switch(m.requete)
    {
      case CONNECT :  
      fprintf(stderr,"(SERVEUR %d) Requete CONNECT reçue de %d\n",getpid(),m.expediteur);
      i=0;
                      while(tab->connexions[i].pidFenetre != 0&&i<6)//on boucle jusqu'a trouve autre chose que 0
                      {
                        i++;
                      }
                      if(i<6)
                      {
                        tab->connexions[i].pidFenetre = m.expediteur;
                      }
                      break; 

      case DECONNECT :  
                      fprintf(stderr,"(SERVEUR %d) Requete DECONNECT reçue de %d\n",getpid(),m.expediteur);
                      i=0;
                      while(m.expediteur!=tab->connexions[i].pidFenetre &&i<6)
                      {
                        i++;
                      }
                      if(m.expediteur==tab->connexions[i].pidFenetre)
                      {
                        tab->connexions[i].pidFenetre= 0;
                        strcpy(tab->connexions[i].nom,"");
                      }


                      break; 

      case LOGIN :  //to do il y a un bug si je me log avec un mot de passe a un characte genre eric-a et je peux quand meme me log avec eric-aa
                    //Il le met dans la liste seulement si tu as crée le compte correctement /login correctement


      {//car on declare la variable posi

      fprintf(stderr,"(SERVEUR %d) Requete LOGIN reçue de %d : --%s--%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2,m.texte);
                     

                    // test si déjà connecté

                      bool estConnecte=false;
                      i=0;

                      while(i<6 && estConnecte==false)
                      {
                          if(strcmp(tab->connexions[i].nom,m.data2)==0)//si nom identique
                          {
                              estConnecte=true;
                          }
                          i++;
                      }

                      // utilisateur déjà connecté
                      if(estConnecte)//== true
                      {
                          // envoie message ko
                          strcpy(reponse.data1, "KO");
                          strcpy(reponse.texte, "Utilisateur déja loggé");
                          reponse.type = m.expediteur;
                          reponse.expediteur = getpid();//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;
                          msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                          kill(m.expediteur,SIGUSR1);
                          break;
                      }

                      bool estNouveau=(strcmp(m.data1,"1")==0);
                      int posi=estPresent(m.data2);

                      // utilisateur pas encore connecté

                      // nouveau && existe
                      if( estNouveau && posi > 0)
                      {
                          // envoie message ko
                          strcpy(reponse.data1, "KO");
                          strcpy(reponse.texte, "Utilisateur déja Existant");
                          reponse.type = m.expediteur;
                          reponse.expediteur = getpid();//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;
                          msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                          kill(m.expediteur,SIGUSR1);
                          break;
                      }

                      // nouveau mais n'existe pas
                      if(estNouveau)
                      {
                        ajouteUtilisateur(m.data2,m.texte);// en gros nom -mdp ajouter dans un fichier


                        //préparation de la réponse//
                        strcpy(reponse.data1, "OK");
                        strcpy(reponse.texte, "Nom créé");
                        reponse.type = m.expediteur;
                        reponse.expediteur = getpid();//probablement car serveur et donc la norme
                        reponse.requete=LOGIN;
                        msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                        kill(m.expediteur,SIGUSR1);
                        


                        i=0;
                        while(i<6 && tab->connexions[i].pidFenetre != m.expediteur)
                          i++;

                        strcpy(tab->connexions[i].nom,m.data2);




                        //sql eric du futur
                        sprintf(requete,"insert into UNIX_FINAL values (NULL,'%s','---','---');",m.data2);//edit j'ai reussi enfaite c'est car je faisais une deconnexion sauf que je ne recrée pas une connexion puisque ca se passe qu'une seul fois
                        mysql_query(connexion,requete);                      
                        fprintf(stderr,"Insertion OK.\n");


                          for(j=0;j<6;j++)
                          {
                              if(tab->connexions[j].pidFenetre && tab->connexions[j].pidFenetre != m.expediteur && strcmp(tab->connexions[j].nom,""))
                              {
                                  //Send adduser expediteur
                                  reponse.type=tab->connexions[j].pidFenetre;
                                  reponse.requete=ADD_USER;
                                  strcpy(reponse.data1,m.data2);
                                  msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                                  kill(tab->connexions[j].pidFenetre,SIGUSR1);

                                  //send adduser user
                                  reponse.type=m.expediteur;
                                  strcpy(reponse.data1,tab->connexions[j].nom);
                                  msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                              }
                          }

                          kill(m.expediteur,SIGUSR1);
                          break;

                      }

                      // pas nouveau et existe pas 
                      if( posi <= 0)
                      {

                          // envoie message ko
                          strcpy(reponse.data1, "KO");
                          strcpy(reponse.texte, "Utilisateur Introuvable");
                          reponse.type = m.expediteur;
                          reponse.expediteur = getpid();//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;
                          msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                          kill(m.expediteur,SIGUSR1);

                          break;
                      }

                      // pas nouveau et existe

                      //mot de passe correct
                      if(verifieMotDePasse(posi,m.texte) == 1)
                      {
                          //send ok
                          strcpy(reponse.data1, "OK");
                          strcpy(reponse.texte, "Rebienvenue cher Utilisateur");
                          reponse.type = m.expediteur;
                          reponse.expediteur = getpid();//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;
                          msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                          kill(m.expediteur,SIGUSR1);

                          i=0;
                          while(i<6 && tab->connexions[i].pidFenetre != m.expediteur)
                            i++;

                          strcpy(tab->connexions[i].nom,m.data2);

                          for(j=0;j<6;j++)
                          {
                              if(tab->connexions[j].pidFenetre && tab->connexions[j].pidFenetre != m.expediteur && strcmp(tab->connexions[j].nom,""))
                              {
                                  //Send adduser expediteur
                                  reponse.type=tab->connexions[j].pidFenetre;
                                  reponse.requete=ADD_USER;
                                  strcpy(reponse.data1,m.data2);
                                  msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                                  kill(tab->connexions[j].pidFenetre,SIGUSR1);

                                  //send adduser user
                                  reponse.type=m.expediteur;
                                  strcpy(reponse.data1,tab->connexions[j].nom);
                                  msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                              }
                          }

                          kill(m.expediteur,SIGUSR1);
                          break;
                      }

                      // mot de passe incorrect    
                      // envoie message ko
                      strcpy(reponse.data1, "KO");
                      strcpy(reponse.texte, "Mot de passe incorrect");
                      reponse.type = m.expediteur;
                      reponse.expediteur = getpid();//probablement car serveur et donc la norme
                      reponse.requete=LOGIN;
                      msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                      kill(m.expediteur,SIGUSR1);    
                      break; 
      }
      case LOGOUT :  //en gros le prof veut juste qu'on remove le nom
      //Eric du futur il n'ya pas de nom envoyé dans le protocole  c'est pour ca qu'il y a une boucle de recherche pour chercher direct sur le tableau du serveur
      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT reçue de %d\n",getpid(),m.expediteur);
      
      
      MESSAGE Deconnexion; // variable temporaire
      for(i=0;i<6;i++)
      {
        if(m.expediteur==tab->connexions[i].pidFenetre)
        {
          strcpy(Deconnexion.data1,tab->connexions[i].nom);
          Deconnexion.requete = REMOVE_USER;
          Deconnexion.expediteur = 1;
          strcpy(tab->connexions[i].nom,"");//ca clean le tableau
          for(j=0;j<5;j++)//on va clean le champs autre
          {
            tab->connexions[i].autres[j]=0;
          }
          i=6;

        }
      }


      for(i=0;i<6;i++)//je clean sur les autrees  pid 
      {
        for(j=0;j<5;j++)
        {
          if(m.expediteur==tab->connexions[i].autres[j])
          {
            tab->connexions[i].autres[j]=0;
          }
        }
      }


      

      for (int i = 0; i < 6; i++)
      {
        if (tab->connexions[i].pidFenetre != 0 && strcmp(tab->connexions[i].nom, m.data2) != 0 && strcmp(tab->connexions[i].nom,"") != 0)
        {
          Deconnexion.type = tab->connexions[i].pidFenetre;
          
          
          msgsnd(idQ, &Deconnexion, sizeof(MESSAGE) - sizeof(long), 0);

          fprintf(stderr, "(Le pid de l'expéditeur %d envoie au pid du destinataire %d avec comme data1 %s)\n", Deconnexion.expediteur, Deconnexion.type, Deconnexion.data1);
          kill(Deconnexion.type, SIGUSR1);
        }
      }









      
      break;

      case ACCEPT_USER :

      fprintf(stderr,"(SERVEUR %d) Requete ACCEPT_USER reçue de %d\n",getpid(),m.expediteur);
      fprintf(stderr,"notre pid:(%d)->(%d) avec comme data1 %s avec comme requete %d \n",m.expediteur,m.type,m.data1,m.requete);

      for(k=0;k<6;k++)
      {
        if (tab->connexions[k].pidFenetre !=0 && strcmp(tab->connexions[k].nom,m.data1)==0)//pid m.data1
        {
          for(i=0;i<6;i++)//cherche la ligne de l"expediteur
          {
            if(tab->connexions[i].pidFenetre==m.expediteur)
            {
              for(j=0;j<5;j++)//cherche colone 0 autres libres
              {
                if(tab->connexions[i].autres[j]==0)
                {
                  tab->connexions[i].autres[j]=tab->connexions[k].pidFenetre;
                  j=5;
                }
              }
            }
          }
        }
      }
      
      fprintf(stderr,"tab mise a jour\n");


      break;

      case REFUSE_USER :
      fprintf(stderr,"(SERVEUR %d) Requete REFUSE_USER reçue de %d\n",getpid(),m.expediteur);



      for(k=0;k<6;k++)
      {
        if (tab->connexions[k].pidFenetre !=0 && strcmp(tab->connexions[k].nom,m.data1)==0)//pid m.data1
        {
          for(i=0;i<6;i++)//cherche la ligne de l"expediteur
          {
            if(tab->connexions[i].pidFenetre==m.expediteur)
            {
              for(j=0;j<5;j++)//cherche le pid du M.data1 dans le champs autre 
              {
                if(tab->connexions[i].autres[j]==tab->connexions[k].pidFenetre)
                {
                  tab->connexions[i].autres[j]=0;
                  j=5;
                }
              }
            }
          }
        }
      }

      fprintf(stderr,"tab mise a jour\n");

      break;

      case SEND :  

      fprintf(stderr,"(SERVEUR %d) Requete SEND reçue de %d\n",getpid(),m.expediteur);

      i=0;
      while(i<6 && tab->connexions[i].pidFenetre != m.expediteur)i++;

      for(j=0;j<5;j++)
      {
        if(tab->connexions[i].autres[j])
        {
          reponse.type=tab->connexions[i].autres[j];
          reponse.expediteur=getpid();
          reponse.requete=SEND;
          strcpy(reponse.data1,tab->connexions[i].nom);
          strcpy(reponse.texte,m.texte);
          msgsnd(idQ,&reponse,sizeof(MESSAGE) - sizeof(long), 0);
          kill(reponse.type,SIGUSR1);
        }
      }

      break; 

      case UPDATE_PUB :
      fprintf(stderr,"(SERVEUR %d) Requete UPDATE_PUB reçue de %d\n",getpid(),m.expediteur);

      MESSAGE Update_Publicite;

      Update_Publicite.expediteur=m.expediteur;


      for(i=0;i<6;i++)
      {
        if(tab->connexions[i].pidFenetre!=0)
        {
          Update_Publicite.type=tab->connexions[i].pidFenetre;
          msgsnd(idQ,&Update_Publicite,sizeof(MESSAGE) - sizeof(long), 0);
          kill(Update_Publicite.type,SIGUSR2);

        }
      }







      break;

      case CONSULT :
      fprintf(stderr,"(SERVEUR %d) Requete CONSULT reçue de %d\n",getpid(),m.expediteur);

      MESSAGE consultation;
      int ConsultationFIls;

      ConsultationFIls=fork();

      if(ConsultationFIls==0)
      {
        execl("./Consultation","Consultation",(char*)NULL);
      }
            m.type=ConsultationFIls;


      msgsnd(idQ,&m,sizeof(MESSAGE) - sizeof(long), 0);

      fprintf(stderr,"le pid du fiddls %d\n",ConsultationFIls);


      break;

      case MODIF1 : //pourqui le pid fait n'imp si je ne consulte pas avant
      fprintf(stderr,"(SERVEUR %d) Requete MODIF1 reçue de %d\n",getpid(),m.expediteur);

      int ModificationFils;

      ModificationFils=fork();

      if(ModificationFils==0)
      {
        execl("./Modification","Modification",(char*)NULL);
      }

      for(i=0;i<6;i++)
      {
        if(m.expediteur==tab->connexions[i].pidFenetre)
        {
          strcpy(m.data1,tab->connexions[i].nom);
          m.type=ModificationFils;
          tab->connexions[i].pidModification=m.type; //pour montrer le pid du processus je suis trop debile de l'avoir mit hors de la boucle
          i=6;
        }
      }





      msgsnd(idQ,&m,sizeof(MESSAGE) - sizeof(long), 0);




      fprintf(stderr,"le pid du fiddls %d\n",ModificationFils);



      break;

      case MODIF2 :
      fprintf(stderr,"(SERVEUR %d) Requete MODIF2 reçue de %d\n",getpid(),m.expediteur);
      

      for(i=0;i<6;i++)
      {
        if(m.expediteur==tab->connexions[i].pidFenetre)
        {
          m.type=tab->connexions[i].pidModification;
          fprintf(stderr,"(SERVEUR %d)pid du type%d\n",getpid(),m.type);
          i=6;
        }
      }

      msgsnd(idQ,&m,sizeof(MESSAGE) - sizeof(long), 0);


      break;

      case LOGIN_ADMIN :
      fprintf(stderr,"(SERVEUR %d) Requete LOGIN_ADMIN reçue de %d\n",getpid(),m.expediteur);
      break;

      case LOGOUT_ADMIN :
      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT_ADMIN reçue de %d\n",getpid(),m.expediteur);
      break;

      case NEW_USER :
      fprintf(stderr,"(SERVEUR %d) Requete NEW_USER reçue de %d : --%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2);
      break;

      case DELETE_USER :
      fprintf(stderr,"(SERVEUR %d) Requete DELETE_USER reçue de %d : --%s--\n",getpid(),m.expediteur,m.data1);
      break;

      case NEW_PUB :
      fprintf(stderr,"(SERVEUR %d) Requete NEW_PUB reçue de %d\n",getpid(),m.expediteur);
      break;
    }
    afficheTab();
  }
}

void afficheTab()
{
  fprintf(stderr,"Pid Serveur 1 : %d\n",tab->pidServeur1);
  fprintf(stderr,"Pid Serveur 2 : %d\n",tab->pidServeur2);
  fprintf(stderr,"Pid Publicite : %d\n",tab->pidPublicite);
  fprintf(stderr,"Pid Admin     : %d\n",tab->pidAdmin);
  for (int i=0 ; i<6 ; i++)
    fprintf(stderr,"%6d -%20s- %6d %6d %6d %6d %6d - %6d\n",tab->connexions[i].pidFenetre,
      tab->connexions[i].nom,
      tab->connexions[i].autres[0],
      tab->connexions[i].autres[1],
      tab->connexions[i].autres[2],
      tab->connexions[i].autres[3],
      tab->connexions[i].autres[4],
      tab->connexions[i].pidModification);
  fprintf(stderr,"\n");
}


///1.3///

//controle c
void HandlerSIGINT(int sig)
{
  (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 


  msgctl(idQ,IPC_RMID,NULL);
  shmctl(ShID,IPC_RMID,NULL);
  if (semctl(idSem,0,IPC_RMID) == -1)
  {
  perror("Erreur de semctl (1)");
  exit(1);
  }
  exit(0);

}

void HandlerSIGCHLD(int sig)
{
  (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 

         
  int id,statut;



  //il attends un fils mort !! a test 
  id=wait(&statut);
  fprintf(stderr,"Sig:%d, EX:%d \n",WIFSIGNALED(statut),WIFEXITED(statut));//pour eric du futur pour debug
  for(int i=0;i<6;i++)
  {
    if(tab->connexions[i].pidModification==id)
      tab->connexions[i].pidModification=0;
  }
  fprintf(stderr,"(SERVEUR) Suspression du processus Zombie %d\n",id);
  siglongjmp(flag,1);


}