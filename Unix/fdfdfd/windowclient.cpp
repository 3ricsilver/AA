#include "windowclient.h"
#include "ui_windowclient.h"
#include <QMessageBox>
#include "dialogmodification.h"
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>

#include <sys/shm.h>

extern WindowClient *w;

#include "protocole.h"

int idQ, idShm;

#define TIME_OUT 120
int timeOut = TIME_OUT;

PUBLICITE *PubSus;//memoire partagé

void handlerSIGUSR1(int sig);//to do a armer 
//etape 3////////////////////
void handlerSIGALRM(int sig);//to do  a faire
//////////////////


///////4////////////////////
void HandlerSIGUSR2(int sig);
////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
    ui->setupUi(this);
    ::close(2);
    logoutOK();

    // Recuperation de l'identifiant de la file de messages
    fprintf(stderr,"(CLIENT %d) Recuperation de l'id de la file de messages\n",getpid());

    ///////////////////1///////////////


      if ((idQ = msgget(CLE,0)) == -1)
      {
      perror("Erreur de msgget");
      exit(1);
      }

    ///////////////////////////////
    // Recuperation de l'identifiant de la mémoire partagée
    fprintf(stderr,"(CLIENT %d) Recuperation de l'id de la mémoire partagée\n",getpid());


    if((idShm =shmget(CLE,0,0))==-1)
    {
      perror("Erreur de shmget");
      exit(1);
    }


    // Attachement à la mémoire partagée


   if ((PubSus = (PUBLICITE*)shmat(idShm,NULL,SHM_RDONLY)) == (PUBLICITE*)-1)
   {
       perror("Erreur de shmat");
       exit(1);
   }

    // Armement des signaux

    //le truc qui recoit les requetes serveurs

    struct sigaction dz;//o a test
    dz.sa_handler = handlerSIGUSR1;
    sigemptyset(&dz.sa_mask);
    dz.sa_flags = 0;
    sigaction(SIGUSR1,&dz,NULL);

    ///ARMEment du time out 

    struct sigaction out;//o a test
    out.sa_handler = handlerSIGALRM;
    sigemptyset(&out.sa_mask);
    out.sa_flags = 0;
    sigaction(SIGALRM,&out,NULL);



      ////4/////////////////
     struct sigaction dbz;//on arme un signal pour qu'il ignore
     dbz.sa_handler = HandlerSIGUSR2;//int sig n'est pas utilisé et correspond au numero du signal
     sigemptyset(&dbz.sa_mask);
     dbz.sa_flags = 0;
     sigaction(SIGUSR2,&dbz,NULL);
      // :::::::::::::::::::::::::



    // Envoi d'une requete de connexion au serveur //type 1 

    MESSAGE connexion1;//en gros struct que je vais utiliser pour remplier et puis send les infos au serveur
    connexion1.type=1;
    connexion1.expediteur=getpid();
    connexion1.requete=CONNECT;



    if(msgsnd(idQ,&connexion1,sizeof(MESSAGE)-sizeof(long),0)==-1)
    {
      perror("Erreur de msgsnd");
      exit(1);
    }


}

WindowClient::~WindowClient()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setNom(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditNom->clear();
    return;
  }
  ui->lineEditNom->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getNom()
{
  strcpy(connectes[0],ui->lineEditNom->text().toStdString().c_str());
  return connectes[0];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setMotDePasse(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditMotDePasse->clear();
    return;
  }
  ui->lineEditMotDePasse->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getMotDePasse()
{
  strcpy(motDePasse,ui->lineEditMotDePasse->text().toStdString().c_str());
  return motDePasse;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WindowClient::isNouveauChecked()
{
  if (ui->checkBoxNouveau->isChecked()) return 1;
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setPublicite(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditPublicite->clear();
    return;
  }
  ui->lineEditPublicite->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setTimeOut(int nb)
{
  ui->lcdNumberTimeOut->display(nb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setAEnvoyer(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditAEnvoyer->clear();
    return;
  }
  ui->lineEditAEnvoyer->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getAEnvoyer()
{
  strcpy(aEnvoyer,ui->lineEditAEnvoyer->text().toStdString().c_str());
  return aEnvoyer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setPersonneConnectee(int i,const char* Text)
{
  if (strlen(Text) == 0 )
  {
    switch(i)
    {
        case 1 : ui->lineEditConnecte1->clear(); break;
        case 2 : ui->lineEditConnecte2->clear(); break;
        case 3 : ui->lineEditConnecte3->clear(); break;
        case 4 : ui->lineEditConnecte4->clear(); break;
        case 5 : ui->lineEditConnecte5->clear(); break;
    }
    return;
  }
  switch(i)
  {
      case 1 : ui->lineEditConnecte1->setText(Text); break;
      case 2 : ui->lineEditConnecte2->setText(Text); break;
      case 3 : ui->lineEditConnecte3->setText(Text); break;
      case 4 : ui->lineEditConnecte4->setText(Text); break;
      case 5 : ui->lineEditConnecte5->setText(Text); break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getPersonneConnectee(int i)
{
  QLineEdit *tmp;
  switch(i)
  {
    case 1 : tmp = ui->lineEditConnecte1; break;
    case 2 : tmp = ui->lineEditConnecte2; break;
    case 3 : tmp = ui->lineEditConnecte3; break;
    case 4 : tmp = ui->lineEditConnecte4; break;
    case 5 : tmp = ui->lineEditConnecte5; break;
    default : return NULL;
  }

  strcpy(connectes[i],tmp->text().toStdString().c_str());
  return connectes[i];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::ajouteMessage(const char* personne,const char* message)
{
  // Choix de la couleur en fonction de la position
  int i=1;
  bool trouve=false;
  while (i<=5 && !trouve)
  {
      if (getPersonneConnectee(i) != NULL && strcmp(getPersonneConnectee(i),personne) == 0) trouve = true;
      else i++;
  }
  char couleur[40];
  if (trouve)
  {
      switch(i)
      {
        case 1 : strcpy(couleur,"<font color=\"red\">"); break;
        case 2 : strcpy(couleur,"<font color=\"blue\">"); break;
        case 3 : strcpy(couleur,"<font color=\"green\">"); break;
        case 4 : strcpy(couleur,"<font color=\"darkcyan\">"); break;
        case 5 : strcpy(couleur,"<font color=\"orange\">"); break;
      }
  }
  else strcpy(couleur,"<font color=\"black\">");
  if (strcmp(getNom(),personne) == 0) strcpy(couleur,"<font color=\"purple\">");

  // ajout du message dans la conversation
  char buffer[300];
  sprintf(buffer,"%s(%s)</font> %s",couleur,personne,message);
  ui->textEditConversations->append(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setNomRenseignements(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditNomRenseignements->clear();
    return;
  }
  ui->lineEditNomRenseignements->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getNomRenseignements()
{
  strcpy(nomR,ui->lineEditNomRenseignements->text().toStdString().c_str());
  return nomR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setGsm(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditGsm->clear();
    return;
  }
  ui->lineEditGsm->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setEmail(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditEmail->clear();
    return;
  }
  ui->lineEditEmail->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setCheckbox(int i,bool b)
{
  QCheckBox *tmp;
  switch(i)
  {
    case 1 : tmp = ui->checkBox1; break;
    case 2 : tmp = ui->checkBox2; break;
    case 3 : tmp = ui->checkBox3; break;
    case 4 : tmp = ui->checkBox4; break;
    case 5 : tmp = ui->checkBox5; break;
    default : return;
  }
  tmp->setChecked(b);
  if (b) tmp->setText("Accepté");
  else tmp->setText("Refusé");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::loginOK()
{
  ui->pushButtonLogin->setEnabled(false);
  ui->pushButtonLogout->setEnabled(true);
  ui->lineEditNom->setReadOnly(true);
  ui->lineEditMotDePasse->setReadOnly(true);
  ui->checkBoxNouveau->setEnabled(false);
  ui->pushButtonEnvoyer->setEnabled(true);
  ui->pushButtonConsulter->setEnabled(true);
  ui->pushButtonModifier->setEnabled(true);
  ui->checkBox1->setEnabled(true);
  ui->checkBox2->setEnabled(true);
  ui->checkBox3->setEnabled(true);
  ui->checkBox4->setEnabled(true);
  ui->checkBox5->setEnabled(true);
  ui->lineEditAEnvoyer->setEnabled(true);
  ui->lineEditNomRenseignements->setEnabled(true);
  setTimeOut(TIME_OUT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::logoutOK()
{
  ui->pushButtonLogin->setEnabled(true);
  ui->pushButtonLogout->setEnabled(false);
  ui->lineEditNom->setReadOnly(false);
  ui->lineEditNom->setText("");
  ui->lineEditMotDePasse->setReadOnly(false);
  ui->lineEditMotDePasse->setText("");
  ui->checkBoxNouveau->setEnabled(true);
  ui->pushButtonEnvoyer->setEnabled(false);
  ui->pushButtonConsulter->setEnabled(false);
  ui->pushButtonModifier->setEnabled(false);
  for (int i=1 ; i<=5 ; i++)
  {
      setCheckbox(i,false);
      setPersonneConnectee(i,"");
  }
  ui->checkBox1->setEnabled(false);
  ui->checkBox2->setEnabled(false);
  ui->checkBox3->setEnabled(false);
  ui->checkBox4->setEnabled(false);
  ui->checkBox5->setEnabled(false);
  setNomRenseignements("");
  setGsm("");
  setEmail("");
  ui->textEditConversations->clear();
  setAEnvoyer("");
  ui->lineEditAEnvoyer->setEnabled(false);
  ui->lineEditNomRenseignements->setEnabled(false);
  setTimeOut(TIME_OUT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::closeEvent(QCloseEvent *event)
{
    timeOut=120;


  /////////////////////1////////////////////////////
    // TO DO en gros requete de deconnection
    MESSAGE deconnexion1;//en gros struct que je vais utiliser pour remplier et puis send les infos au serveur
    deconnexion1.type=1;
    deconnexion1.expediteur=getpid();
    deconnexion1.requete=DECONNECT;




    if(msgsnd(idQ,&deconnexion1,sizeof(MESSAGE)-sizeof(long),0)==-1)
    {
      perror("Erreur de msgsnd");
      exit(1);
    }
  /////////////////////////////////////////////////
    /////////1.2////////////////
    MESSAGE PushLogout;
    PushLogout.expediteur=getpid();
    PushLogout.type=1;

    PushLogout.requete=LOGOUT;

    msgsnd(idQ,&PushLogout,sizeof(MESSAGE)-sizeof(long),0);

    QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonLogin_clicked()
{
    timeOut=120;

  /////////////////////1/////////////////////

  MESSAGE PushLogin;
  

  //sprintf permet de reconvertir en chaine de charactere
  //sprintf(msg,"%d",x)
  //y= atoi(msg); permet de reconvertir le char en int on devra faire ca coté serveur en supposant que y est un int askip selon prof je vais devoir use ca pour serveur -> client perso j'ai pas use

  sprintf(PushLogin.data1,"%d",isNouveauChecked()); //méthode qui renvoie 0 ou 1 pour savoir si c'est un nv user ou non 
  strcpy(PushLogin.data2,getNom());
  strcpy(PushLogin.texte,getMotDePasse());

  PushLogin.expediteur=getpid();
  PushLogin.type=1;

  PushLogin.requete=LOGIN;

  msgsnd(idQ,&PushLogin,sizeof(MESSAGE)-sizeof(long),0);// la condition verif m'empeche d'envoyer 
  

  /////////////////////////////////////////
}

void WindowClient::on_pushButtonLogout_clicked()
{
    timeOut=120;

    MESSAGE PushLogout;
    PushLogout.expediteur=getpid();
    PushLogout.type=1;

    PushLogout.requete=LOGOUT;

    msgsnd(idQ,&PushLogout,sizeof(MESSAGE)-sizeof(long),0);// la condition verif m'empeche d'envoyer 
  
    logoutOK();
}

void WindowClient::on_pushButtonEnvoyer_clicked()
{
   timeOut=120;

    MESSAGE MessageEnvoyer;
    MessageEnvoyer.expediteur=getpid();
    MessageEnvoyer.type=1;

    strcpy(MessageEnvoyer.texte,getAEnvoyer());

    MessageEnvoyer.requete=SEND;

    msgsnd(idQ,&MessageEnvoyer,sizeof(MESSAGE)-sizeof(long),0);



}

void WindowClient::on_pushButtonConsulter_clicked()
{
    timeOut=120;

    MESSAGE consultation;

    consultation.expediteur=getpid();
    consultation.type=1;

    strcpy(consultation.data1,getNomRenseignements());

    consultation.requete=CONSULT;

    msgsnd(idQ,&consultation,sizeof(MESSAGE)-sizeof(long),0);

}

void WindowClient::on_pushButtonModifier_clicked()
{
  timeOut=120;

  // TO DO
  // Envoi d'une requete MODIF1 au serveur
  MESSAGE m;
  // ...

  // Attente d'une reponse en provenance de Modification
  fprintf(stderr,"(CLIENT %d) Attente reponse MODIF1\n",getpid());
  // ...

  // Verification si la modification est possible
  if (strcmp(m.data1,"KO") == 0 && strcmp(m.data2,"KO") == 0 && strcmp(m.texte,"KO") == 0)
  {
    QMessageBox::critical(w,"Problème...","Modification déjà en cours...");
    return;
  }

  // Modification des données par utilisateur
  DialogModification dialogue(this,getNom(),"",m.data2,m.texte);
  dialogue.exec();
  char motDePasse[40];
  char gsm[40];
  char email[40];
  strcpy(motDePasse,dialogue.getMotDePasse());
  strcpy(gsm,dialogue.getGsm());
  strcpy(email,dialogue.getEmail());

  // Envoi des données modifiées au serveur
  // ...
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les checkbox ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_checkBox1_clicked(bool checked)//par defaut tout est refusé 
{
    MESSAGE UserAccepter;
    timeOut=120;


    if (checked)
    {
        ui->checkBox1->setText("Accepté");//accept_user 88 ustiliser getpersonneconnecter

        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(1));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=ACCEPT_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
        

        
    }
    else
    {
        ui->checkBox1->setText("Refusé");

        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(1));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=REFUSE_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
}

void WindowClient::on_checkBox2_clicked(bool checked)
{
    MESSAGE UserAccepter;
    timeOut=120;


    if (checked)
    {
        ui->checkBox2->setText("Accepté");
        
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(2));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=ACCEPT_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
    else
    {
        ui->checkBox2->setText("Refusé");
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(2));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=REFUSE_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
}

void WindowClient::on_checkBox3_clicked(bool checked)
{
    MESSAGE UserAccepter;
    timeOut=120;


    if (checked)
    {
        ui->checkBox3->setText("Accepté");
       
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(3));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=ACCEPT_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
    else
    {
        ui->checkBox3->setText("Refusé");
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(3));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=REFUSE_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
}

void WindowClient::on_checkBox4_clicked(bool checked)
{
    timeOut=120;

    MESSAGE UserAccepter;

    if (checked)
    {
        ui->checkBox4->setText("Accepté");
        
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(4));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=ACCEPT_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
    else
    {
        ui->checkBox4->setText("Refusé");
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(4));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=REFUSE_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
}

void WindowClient::on_checkBox5_clicked(bool checked)
{


    timeOut=120;

    MESSAGE UserAccepter;

    if (checked)
    {
        ui->checkBox5->setText("Accepté");
        
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(5));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=ACCEPT_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
    else
    {
        ui->checkBox5->setText("Refusé");
        UserAccepter.type=1;
        UserAccepter.expediteur=getpid();
        strcpy(UserAccepter.data1,w->getPersonneConnectee(5));//je le mets de maniere sale car pas besoin de plus
        UserAccepter.requete=REFUSE_USER;

        msgsnd(idQ,&UserAccepter,sizeof(MESSAGE)-sizeof(long),0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handlerSIGUSR1(int sig)
{
    (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 

    MESSAGE m;
    /////2.0/////////
    int i;
    /////////////////

    //TO DO 2
    // Le client peut recevoir bcp de message à lire en un kill() donc on met un while et une fois qu’il a fini de tout lire il sort du handler
    // Si tu mettais seulement un if il irait une seule fois et donc des messages pourraient rester sur la file de messsge
    while(msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),getpid(),IPC_NOWAIT)!=-1)//NO WAIT POUR RECEVOIR PLUSIEURS
    {
    

    
      switch(m.requete)
      {
        case LOGIN :
                    if (strcmp(m.data1,"OK") == 0)
                    {
                      fprintf(stderr,"(CLIENT %d) Login OK\n",getpid());
                      w->loginOK();
                      w->dialogueMessage("Login...",m.texte);
                      //...
                      timeOut=120;
                      alarm(1);


                    }
                    else w->dialogueErreur("Login...",m.texte);
                    break;

        case ADD_USER :
                    //2.0///////////////////////////////
                      
                    timeOut=120;

                    for(i=1;i<6;i++)
                    {
                      if((strcmp(w->getPersonneConnectee(i),"")==0))
                      {
                         w->setPersonneConnectee(i,m.data1);
                         i=6;


                      }
                    }
                    // ////////////////////////////////////::
                    break;

        case REMOVE_USER :
                    //to do tu utiliser get pour avoir la position de la personne a supprmé
                    timeOut=120;

                    for(i=1;i<6;i++)
                    {
                      if((strcmp(w->getPersonneConnectee(i),m.data1)==0))
                      {
                         w->setPersonneConnectee(i,"");
                         i=6;


                      }
                    }
                    break;

        case SEND :
                    timeOut=120;

                    w->ajouteMessage(m.data1,m.texte);
                    break;

        case CONSULT :

                  timeOut=120;

                  if(strcmp(m.data1,"OK")==0)
                  {
                    w->setGsm(m.data2);
                    w->setEmail(m.texte);

                  }
                  else
                  {
                    w->setGsm(m.data2);
                    w->setEmail(m.texte);
                  }


                   break;
      }
  } 
}

/*copier coller pour debug j'en avais marre de le récrire

fprintf(stderr,"notre pid:(%d)->(%d) avec comme data1 %s et data2%s avec comme requetec%d \n",m.expediteur,m.type,m.data1,m.data2,m.requete);


*/


void handlerSIGALRM(int sig)
{

  (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 



    timeOut--;
    w->setTimeOut(timeOut);
    if(timeOut==0)
    {
      MESSAGE Timer;
      Timer.expediteur=getpid();
      Timer.type=1;

      Timer.requete=LOGOUT;

      msgsnd(idQ,&Timer,sizeof(MESSAGE)-sizeof(long),0);// la condition verif m'empeche d'envoyer 
  
      w->logoutOK();
    }
    else
    {
      alarm(1);//il renvoie un signal     
    }

}


void HandlerSIGUSR2(int sig)
{
    (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 


    
     w->setPublicite(PubSus->texte);


}