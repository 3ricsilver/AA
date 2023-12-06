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

int idQ,idShm,idSem;
TAB_CONNEXIONS *tab;

void afficheTab();

MYSQL* connexion;
/////1.3/////////////////////
void HandlerSIGINT(int sig);
/////////////////////////////

int main()
{
  ////1.3/////////////////
  struct sigaction dz;//on arme un signal pour qu'il ignore
  dz.sa_handler = HandlerSIGINT;//int sig n'est pas utilisé et correspond au numero du signal
  sigemptyset(&dz.sa_mask);
  dz.sa_flags = 0;
  sigaction(SIGINT,&dz,NULL);
  // :::::::::::::::::::::::::



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

  // Creation du processus Publicite

  int i,k,j;
  MESSAGE m;
  MESSAGE reponse;
  char requete[200];
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  PUBLICITE pub;

  while(1)
  {
  	fprintf(stderr,"(SERVEUR %d) Attente d'une requete...\n",getpid());
    if (msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),1,0) == -1)
    {
      perror("(SERVEUR) Erreur de msgrcv");
      msgctl(idQ,IPC_RMID,NULL);
      exit(1);
    }

    switch(m.requete)
    {
      case CONNECT :  
                      fprintf(stderr,"(SERVEUR %d) Requete CONNECT reçue de %d\n",getpid(),m.expediteur);
                      i=0;
                      while(tab->connexions[i].pidFenetre != 0)//on boucle jusqu'a trouve autre chose que 0
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
                      while(m.expediteur!=tab->connexions[i].pidFenetre)
                      {
                        i++;
                      }
                      if(m.expediteur==tab->connexions[i].pidFenetre)
                      {
                        tab->connexions[i].pidFenetre= 0;
                      }
                      break; 

      case LOGIN :  //to do remove mes fprintf qui sert a debuguer non neccessaire //to do 2 corriger le msgsnd le reste est juste (edit je suis trop con fallait use SIGURS1 envie de me pendre)
                    //Il le met dans la liste seulement si tu as crée le compte correctement /login correctement
                      fprintf(stderr,"(SERVEUR %d) Requete LOGIN reçue de %d : --%s--%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2,m.texte);
                      //to do etape 1.2// faire renvoyer a client et verif si le mot de passe et juste je dois probablement faire un while
                      if(strcmp(m.data1,"1")==0)//cas ou ils veut se login// en gros 0= déja crée 1=il veut crrée un compte
                      {
                        fprintf(stderr,"(Creation de compte)\n");
                        if(estPresent(m.data2)>0)//verifie sI LE PSEUDO EXISTE DÉJA
                        {
                          fprintf(stderr,"(Ton pseudo est déja prit\n");
                        //je remplis la réponse wallah
                        strcpy(reponse.data1,"KO");
                        strcpy(reponse.texte,"Nom déja prit");
                        reponse.type=m.expediteur;
                        reponse.expediteur=1;//probablement car serveur et donc la norme
                        reponse.requete=LOGIN;

                        msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0); //en gros j'envoie au client nom déja prit
                        kill(reponse.type,SIGUSR1);// Pour envoyer un signal 


                        }

                        else//cas ou le nom existe pas on le crée
                        {
                          fprintf(stderr,"(le pseudo existe pas ben je te le crée)\n");

                          //Update pour les nom dans son machin avec les noms
                          fprintf(stderr,"(Update des nom dans la liste Serveur)\n");
                          i=0;
                          while(tab->connexions[i].pidFenetre != m.expediteur && i<6)//on boucle jusqu'a il ezreouve le pid ou qu'il depasse 6 itération
                          {
                            i++;
                          }
                          if(i<6)
                          {
                              strcpy(tab->connexions[i].nom,m.data2); 
                          }
                         ajouteUtilisateur(m.data2,m.texte);// en gros nom -mdp ajouter dans un fichier
                         //préparation de la réponse//
                         strcpy(reponse.data1, "OK");
                         strcpy(reponse.texte, "Nom créé");
                         reponse.type = m.expediteur;
                         reponse.expediteur = 1;//probablement car serveur et donc la norme
                         reponse.requete=LOGIN;

                         msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                         kill(reponse.type,SIGUSR1);// Pour envoyer un signal
                         
                        }
                      }//cas ou on veut se log in avec un compte
                      else
                      {
                        fprintf(stderr,"(Login de compte)\n");//pourquoi toujours ici malgré le fait que la valeur soit 0 ou 1
                        if(estPresent(m.data2)>0)//si le nom est présent
                        {
                          if(verifieMotDePasse(estPresent(m.data2),m.texte)==1)//check le password //valide password ou non 
                          {
                            fprintf(stderr,"(Mot de passe correct)\n");

                            //Update pour les nom dans son machin avec les noms
                            fprintf(stderr,"(Update des nom dans la liste Serveur)\n");
                             i=0;
                             while(tab->connexions[i].pidFenetre != m.expediteur && i<6)//on boucle jusqu'a il ezreouve le pid ou qu'il depasse 6 itération
                             {
                                i++;
                             }
                             if(i<6)
                             {

                                strcpy(tab->connexions[i].nom,m.data2);

                             }
                          //préparation de la réponse//
                          strcpy(reponse.data1,"OK");
                          strcpy(reponse.texte,"Rebonjour utilisateur");
                          reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                          }
                          else//si pas le bon mdp
                          {
                          fprintf(stderr,"(Mot de passe incorrect)\n");
                          strcpy(reponse.data1,"KO");
                          strcpy(reponse.texte,"Mot de passe incorrect");
                          reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                          }
                        }
                        else//cas ou le nom existe pas
                        {
                          fprintf(stderr,"(Ton pseudo n'hésite pas tu as fait une Eric)\n");
                          strcpy(reponse.data1,"KO");
                          strcpy(reponse.texte,"Nom Inconnu");
                          reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;
                            
                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                        }
                      }

                      
                      
                      break; 

      case LOGOUT :  //en gros le prof veut juste qu'on remove le nom
                      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT reçue de %d\n",getpid(),m.expediteur);
                      strcpy(tab->connexions[i].nom,"");
                      break;

      case ACCEPT_USER :
                      fprintf(stderr,"(SERVEUR %d) Requete ACCEPT_USER reçue de %d\n",getpid(),m.expediteur);
                      break;

      case REFUSE_USER :
                      fprintf(stderr,"(SERVEUR %d) Requete REFUSE_USER reçue de %d\n",getpid(),m.expediteur);
                      break;

      case SEND :  
                      fprintf(stderr,"(SERVEUR %d) Requete SEND reçue de %d\n",getpid(),m.expediteur);
                      break; 

      case UPDATE_PUB :
                      fprintf(stderr,"(SERVEUR %d) Requete UPDATE_PUB reçue de %d\n",getpid(),m.expediteur);
                      break;

      case CONSULT :
                      fprintf(stderr,"(SERVEUR %d) Requete CONSULT reçue de %d\n",getpid(),m.expediteur);
                      break;

      case MODIF1 :
                      fprintf(stderr,"(SERVEUR %d) Requete MODIF1 reçue de %d\n",getpid(),m.expediteur);
                      break;

      case MODIF2 :
                      fprintf(stderr,"(SERVEUR %d) Requete MODIF2 reçue de %d\n",getpid(),m.expediteur);
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

  msgctl(idQ,IPC_RMID,NULL);
  exit(0);

}