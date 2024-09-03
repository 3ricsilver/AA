#include "./presentation/presentation.h"

void *fctThreadFenetreGraphique(void *);
void *fctThreadEvenements(void *);
void *fctThreadStanley(void *);
void *fctThreadEnnemis(void *);
void *fctThreadGuepe(void *);
void *fctThreadChenilleG(void *);
void *fctThreadChenilleD(void *);
void *fctThreadAraigneeG(void *);
void *fctThreadAraigneeD(void *);
void *fctThreadInsecticideG(void *);
void *fctThreadInsecticideD(void *);

void handlerSIGINT(int);
void handlerSIGALRM(int);
void handlerSIGUSR1(int);
void handlerSIGUSR2(int);
void handlerSIGQUIT(int); 

void destructeurVS(void *p);

pthread_cond_t condEvenement;
pthread_cond_t condEchec;

pthread_key_t keySpec;

//crée par moi meme
pthread_key_t keyPositionGuepe;//sert a rien j'avais juste pas compris le principe a l'époque
//

pthread_mutex_t mutexEtatJeu;
pthread_mutex_t mutexEvenement;
pthread_mutex_t mutexEchec;

pthread_t ThreadFenetreGraphique,ThreadEvenements,ThreadStanley,ThreadEnnemis,ThreadGuepe,ThreadChenilleG,ThreadChenilleD,ThreadAraigneeG,ThreadAraigneeD,ThreadInsecticideG,ThreadInsecticideD;
typedef struct
{
int position;
int orientation;
} S_LOCALISATION;


typedef struct
{
    int presence;
    pthread_t tid;
} S_PRESENCE; 

typedef struct
{
    int etatStanley;
    int positionStanley;
    int actionStanley;
    int etatAmis[5];
    S_PRESENCE guepes[2];
    S_PRESENCE chenillesG[5];
    S_PRESENCE chenillesD[7];
    S_PRESENCE araigneesG[5];
    S_PRESENCE araigneesD[5];
    S_PRESENCE insecticidesG[4];
    S_PRESENCE insecticidesD[4];
    int score;
    int nbEchecs;
} S_ETAT_JEU;

S_ETAT_JEU etatJeu = 
     { BAS, 1, NORMAL,//Stanley
       { NORMAL, NORMAL, NORMAL, NORMAL, NORMAL },//amis
       { { AUCUN, 0 }, { AUCUN, 0 } },//guepe
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 } },
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, 
         { AUCUN, 0 }, { AUCUN, 0 } },
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 } },
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 } },
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 } },
       { { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 }, { AUCUN, 0 } },
       0, 0 };

int evenement = AUCUN; 
int echec = AUCUN;

int main(int argc, char* argv[])
{    

    int i;

    ouvrirFenetreGraphique();


    struct sigaction Sigalarm;
    Sigalarm.sa_handler = handlerSIGALRM;
    Sigalarm.sa_flags = 0;
    sigemptyset(&Sigalarm.sa_mask);
    sigaction(SIGALRM, &Sigalarm, NULL);

    struct sigaction Sigint;
    Sigint.sa_handler = handlerSIGINT; 
    Sigint.sa_flags = 0;
    sigemptyset(&Sigint.sa_mask);
    sigaction(SIGINT, &Sigint, NULL);

    struct sigaction Sigusr1;
    Sigusr1.sa_handler = handlerSIGUSR1; 
    Sigusr1.sa_flags = 0;
    sigemptyset(&Sigusr1.sa_mask);
    sigaction(SIGUSR1, &Sigusr1, NULL);

    struct sigaction Sigusr2;
    Sigusr2.sa_handler = handlerSIGUSR2; 
    Sigusr2.sa_flags = 0;
    sigemptyset(&Sigusr2.sa_mask);
    sigaction(SIGUSR2, &Sigusr2, NULL);

    struct sigaction Sigquit;
    Sigquit.sa_handler = handlerSIGQUIT; 
    Sigquit.sa_flags = 0;
    sigemptyset(&Sigquit.sa_mask);
    sigaction(SIGQUIT, &Sigquit, NULL);

    pthread_mutex_init(&mutexEtatJeu,NULL);
    pthread_mutex_init(&mutexEvenement,NULL);
    pthread_mutex_init(&mutexEchec,NULL);

    pthread_cond_init(&condEvenement,NULL);
    pthread_cond_init(&condEchec,NULL);

    pthread_key_create(&keySpec,destructeurVS);

    srand(time(NULL));




    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal    
    sigaddset(&mask, SIGUSR1);//selectionner le signal    
    sigaddset(&mask, SIGUSR2);//selectionner le signal    
    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    pthread_create(&ThreadFenetreGraphique, NULL,fctThreadFenetreGraphique,NULL);//
    pthread_create(&ThreadEvenements, NULL,fctThreadEvenements,NULL);//
    pthread_create(&ThreadStanley,NULL,fctThreadStanley,NULL);
    pthread_create(&ThreadEnnemis,NULL,fctThreadEnnemis,NULL);


    //pour gérer les echecs  en gros les dégats 

    pthread_mutex_lock(&mutexEtatJeu);
    while(etatJeu.nbEchecs<3)
    {
        pthread_mutex_unlock(&mutexEtatJeu);
        pthread_mutex_lock(&mutexEchec);

        while(echec==AUCUN)
        {
            pthread_cond_wait(&condEchec,&mutexEchec);
        }

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.nbEchecs++;
        etatJeu.etatAmis[echec]= TOUCHE;
        pthread_mutex_unlock(&mutexEtatJeu);

        struct timespec IlEst1hDuMat;//help me plz
        IlEst1hDuMat.tv_sec =1;
        IlEst1hDuMat.tv_nsec = 500000000; //O,1 SECONDE
        nanosleep(&IlEst1hDuMat,NULL);

        pthread_mutex_lock(&mutexEtatJeu);//on remet au propre
        etatJeu.etatAmis[echec]=NORMAL;
        echec=AUCUN;
        pthread_mutex_unlock(&mutexEtatJeu);
        pthread_mutex_unlock(&mutexEchec);

        pthread_mutex_lock(&mutexEtatJeu);//ca ne change rie n au code mais ca me pertube de unlock deux fois comme ca mais ca char
    }
    pthread_mutex_unlock(&mutexEtatJeu);


    //attend la mort

    pthread_join(ThreadEvenements,NULL);


    exit(0);

}
//eric du futur fait ca 

void* fctThreadFenetreGraphique(void*)
{

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

 while(true)
 {
  struct timespec temps;
  temps.tv_sec =0;
  temps.tv_nsec = 100000000; //O,1 SECONDE
  restaurerImageInterne(); // restaure l’image initiale du jeu en mémoire
 
 // afficher les personnages, le score, les échecs dans l'image interne du jeu

 pthread_mutex_lock(&mutexEtatJeu);

 afficherStanley(etatJeu.etatStanley,etatJeu.positionStanley,etatJeu.actionStanley);

 for (int i=0 ; i<5 ; i++)
 {
    afficherAmi(i,etatJeu.etatAmis[i]);
 }

 afficherEchecs(etatJeu.nbEchecs);

 afficherScore(etatJeu.score);

 for(int i = 0; i < 2; i++) 
 {
    if(etatJeu.guepes[i].presence == NORMAL)
    {
         afficherGuepe(i);  
    }

 }

 for(int i = 4; i > -1; i--) 
 {
    if(etatJeu.chenillesG[i].presence == NORMAL)
    {
         afficherChenilleG(i);  
    }
 }

 for(int i = 0; i < 7; i++) 
 {
    if(etatJeu.chenillesD[i].presence == NORMAL)
    {
         afficherChenilleD(i);  
    }
 }

 for(int i = 0; i <5; i++) 
 {
    if(etatJeu.araigneesG[i].presence == NORMAL)//j'ai une idée probablement de la merde pour le bug d'affichage quand tu tues avec le truc qui etends mais je vais tenter eric du futur qui le relit tu sais que je penses
    {
         afficherAraigneeG(i);  
    }//pire idée du siecle oublie
 }

 for(int i = 4; i >-1; i--) //il y a une erreur sur le truc de matagne c'est l'inverse du schema qu'il a fait  
 {
    if(etatJeu.araigneesD[i].presence == NORMAL)
    {
         afficherAraigneeD(i);  
    }
 }
 // afficherAraigneeG(4);

 for(int i = 3; i >-1; i--) //il y a une erreur sur le truc de matagne c'est l'inverse du schema qu'il a fait
 {
    if(etatJeu.insecticidesG[i].presence == NORMAL)
    {
         afficherInsecticideG(i);  
    }
 }

 for(int i = 0; i<4; i++) //WTF pourquoi si je definis a 1 ca fait pop un nuage a la posi 4
 {
    if(etatJeu.insecticidesD[i].presence == NORMAL)
    {
         afficherInsecticideD(i);  
    }
 }

 pthread_mutex_unlock(&mutexEtatJeu);


 actualiserFenetreGraphique(); // rendre visible l’image interne du jeu
 nanosleep(&temps, NULL); // attendre 0,1 s 
 }
 pthread_exit(0);
}

void *fctThreadEvenements(void *)
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

    sigaddset(&mask, SIGUSR1);//selectionner le signal

    sigaddset(&mask, SIGINT);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer


    int event;//ca marche si je fais evenement direct mais ca crash au bout d'un moment

    while(1)
    {
        event=lireEvenement();
        pthread_mutex_lock(&mutexEvenement);//en gros pense au feu rouge il attend que le truc soit unlock pour la lock puis on va la manipuler
        evenement=event;
        if(SDL_QUIT==evenement)
        {
            printf("Vrai dz fait ctrl + c");
            exit(0);
        }
        pthread_mutex_unlock(&mutexEvenement);
        pthread_cond_signal(&condEvenement);//send un signal a stan 

        struct timespec temps;
        temps.tv_sec =0;
        temps.tv_nsec = 100000000; //O,1 SECONDE
        nanosleep(&temps, NULL); // attendre 0,1 s 


    }
}

void* fctThreadStanley(void*)//quand tu pourras test pourquoi pas a la place de multiple if pourquoi pas faire une grosse condition genre 0 jusqu'a 4
{

    //pour les sleeep 0.2sec
    struct timespec tempsstan;
    tempsstan.tv_sec =0;
    tempsstan.tv_nsec = 200000000; //O,2 SECONDe 
    //...//apparament selon pompeo c'est masque le signal to do est ce que j'ai juste je sis pas

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer


    while(true)
    {
        pthread_mutex_lock(&mutexEvenement);

        pthread_cond_wait(&condEvenement,&mutexEvenement);

        pthread_mutex_lock(&mutexEtatJeu); 
 
        switch(etatJeu.etatStanley)
        {
            case BAS:
                switch(evenement)
                {
                    case SDLK_SPACE:

                        if(etatJeu.positionStanley == 2)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            for(int i = 0; i < 2; i++)
                            {
                                if(etatJeu.guepes[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.guepes[i].tid, SIGINT);//pourquoi ca crash
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }

                        if(etatJeu.positionStanley == 0)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            
                            if(etatJeu.araigneesG[4].presence == NORMAL)
                            {
                                pthread_kill(etatJeu.araigneesG[4].tid, SIGUSR2);
                            }
                            else
                            {
                                pthread_create(&ThreadInsecticideG, NULL,fctThreadInsecticideG, NULL);
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }


                        if(etatJeu.positionStanley == 3)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            
                            if(etatJeu.araigneesD[0].presence == NORMAL)
                            {
                                pthread_kill(etatJeu.araigneesD[0].tid, SIGUSR2);
                            }
                            else
                            {
                                printf("test gazz gazz droite\n");
                                pthread_create(&ThreadInsecticideD, NULL, fctThreadInsecticideD, NULL);
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }
                        break;
                     case SDLK_LEFT:
                        
                        if(etatJeu.positionStanley > 0)
                        {
                            etatJeu.positionStanley--;
                            printf("GAUCHE bas tu es la\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }

                        break;
                    
                    case SDLK_RIGHT:
                        if(etatJeu.positionStanley <3)
                        {
                            etatJeu.positionStanley++;
                            printf("droite bas\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }
                        break;

                    case SDLK_UP:
                        if(etatJeu.etatStanley == BAS && etatJeu.positionStanley == 1)
                        {
                            etatJeu.etatStanley = ECHELLE;
                            etatJeu.positionStanley = 1;
                        }

                        break;

                }
                break;
        
            case ECHELLE:
                switch(evenement)
                {
                    case SDLK_DOWN:

                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley < 1)
                    {
                        etatJeu.positionStanley++;
                    }

                    else if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 1)
                    {
                        etatJeu.positionStanley=1;
                        etatJeu.etatStanley = BAS;
                    }

                    break;

                    case SDLK_UP:       
                                                
                    if (etatJeu .positionStanley==1)
                    {
                        etatJeu.positionStanley = 0;
                    }

                    else if(etatJeu.positionStanley ==0)
                    {
                            etatJeu.positionStanley = 2;
                            etatJeu.etatStanley =HAUT ;
                    }
                    break;
                 
                }
                break;
        
        case HAUT:
        switch(evenement)
                {
                    case SDLK_SPACE:
                        
                        if(etatJeu.positionStanley == 0)
                        {

                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);

                            etatJeu.actionStanley = SPRAY;
                            for(int i = 0; i < 2; i++)
                            {
                                if(etatJeu.chenillesG[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.chenillesG[i].tid, SIGUSR1);
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }

                        else if(etatJeu.positionStanley == 1)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            for(int i = 2; i < 4; i++)
                            {
                                if(etatJeu.chenillesG[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.chenillesG[i].tid, SIGUSR1);
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }

                        else if(etatJeu.positionStanley == 3)//il est dans la partie droie la 
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            etatJeu.actionStanley = SPRAY;
                            pthread_mutex_lock(&mutexEtatJeu);
                            for(int i = 1; i < 3; i++)
                            {
                                if(etatJeu.chenillesD[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.chenillesD[i].tid, SIGUSR1);
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }

                        else if(etatJeu.positionStanley == 4)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            for(int i = 3; i < 5; i++)
                            {
                                if(etatJeu.chenillesD[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.chenillesD[i].tid, SIGUSR1);
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        }

                        else if(etatJeu.positionStanley == 5)
                        {
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);
                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = SPRAY;
                            for(int i = 5; i < 7; i++)
                            {
                                if(etatJeu.chenillesD[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.chenillesD[i].tid, SIGUSR1);
                                }
                            }
                            pthread_mutex_unlock(&mutexEtatJeu);
                            nanosleep(&tempsstan,NULL);


                            pthread_mutex_lock(&mutexEtatJeu);
                            etatJeu.actionStanley = NORMAL;
                        } 

                        break;
                     case SDLK_LEFT:
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley > 0)
                        {
                            etatJeu.positionStanley--;
                            printf("GAUCHE\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;
                    
                    case SDLK_RIGHT:  
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley <5)
                        {
                            etatJeu.positionStanley++;
                            printf("droite\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;

                    case SDLK_DOWN:
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.etatStanley == HAUT && etatJeu.positionStanley == 2)
                        {
                            etatJeu.etatStanley = ECHELLE;
                            etatJeu.positionStanley = 0;
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;

                }
                break;
            
    }
    pthread_mutex_unlock(&mutexEtatJeu);
    evenement = AUCUN;
    pthread_mutex_unlock(&mutexEvenement);


 }
 pthread_exit(0);
}

void *fctThreadEnnemis(void *)//probablement utiliser des cases ou un vecteur  eric du futur todo
{

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer



            
    alarm(10);//invoquer le saint sig

    int EnnemiAleatoireRandomAuPif;

    //son timer bizzare faut le visualier comme un coffre avec une clée (utilisation du malloc) en gros eric du futur qui relit c'est setspecific c'est comme un coffre avec une clé pour accéder au truc
    int *TimerEnnemieCooldown = (int*)malloc(sizeof(int));//son timer initiale
    *TimerEnnemieCooldown=1600;
    pthread_setspecific(keySpec,(void*)TimerEnnemieCooldown);//c'est le coffre


    while(1)
    {

        EnnemiAleatoireRandomAuPif=rand() % 5;

        //to do enlever le hardcodage du spawn
EnnemiAleatoireRandomAuPif=4;
        switch(EnnemiAleatoireRandomAuPif)
        {
            case 0://GUEPE
                pthread_create(&ThreadGuepe, NULL, fctThreadGuepe, NULL);
                break;
            case 1://ThreadChenilleG
                pthread_create(&ThreadChenilleG, NULL, fctThreadChenilleG, NULL);                
                break;
            case 2://CHENILLE_D
                pthread_create(&ThreadChenilleD, NULL, fctThreadChenilleD, NULL);    
                break;
            case 3://ARAIGNEE_G
                pthread_create(&ThreadAraigneeG, NULL, fctThreadAraigneeG, NULL);
                break;
            case 4://ARAIGNEE_D
                pthread_create(&ThreadAraigneeD, NULL, fctThreadAraigneeD, NULL);
                break;
        }

        struct timespec Lagalere;
        Lagalere.tv_sec = *TimerEnnemieCooldown / 1000; // Seconde donc je vais chopper les 1 secondes car ca va arrondir 1.6 a 1
        Lagalere.tv_nsec = (*TimerEnnemieCooldown % 1000) * 1000000; // 0.6 qui nous faut

        //pour pas spam les mobs
        nanosleep(&Lagalere, NULL);
        //pour test a enlever voir si ca fait bien changer le 1.6 s

        /*free(TimerEnnemieCooldown);//destructeur*/
    }

}



void *fctThreadGuepe(void *)//peut etre envoyer kill pour communiquer avec le sigint
{
    //masque ??
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal

    sigaddset(&mask, SIGUSR2);//selectionner le signal
    sigaddset(&mask, SIGQUIT);//selectionner le signal

    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    sigaddset(&mask, SIGINT);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer


    //eric je ne suis pas sur

    int *PositionGuepe = (int*)malloc(sizeof(int));//la posi

    pthread_setspecific(keySpec,(void*)PositionGuepe);//c'est le coffre

    for(int i = 0; i < 2; i++)
    {
    struct timespec Saiyan;
    Saiyan.tv_sec =1;
    Saiyan.tv_nsec = 500000000; //O,2 SECONDe 
    
        pthread_mutex_lock(&mutexEtatJeu);//case 0
        etatJeu.guepes[i].presence = NORMAL;
        etatJeu.guepes[i].tid = pthread_self();
        *PositionGuepe=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        sleep(1);
        
  
        if(etatJeu.guepes[i].presence == NORMAL && i == 1)//en gros toucher chat le truc du b en gros
        {
            pthread_mutex_lock(&mutexEchec);
            echec = CHAT;
            pthread_cond_signal(&condEchec);
            pthread_mutex_unlock(&mutexEchec);

            pthread_mutex_lock(&mutexEtatJeu);
            etatJeu.guepes[i].presence = AUCUN;
            pthread_mutex_unlock(&mutexEtatJeu);

            nanosleep(&Saiyan,NULL);
        }


        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.guepes[i].presence = AUCUN;//clean derriere en gros passage eric
        pthread_mutex_unlock(&mutexEtatJeu);
        *PositionGuepe=i;

    }

    pthread_exit(0);
}


void *fctThreadChenilleG(void *)//commence a 4 jusuq'a 0 || ILS ONT UNE STRUCT POSITION ET ORIENTATION (VARIABLE SPÉCIFIQUE EGALEMENT) || 0.8s de move
{


    //MASQUE A MODIF //ERIC DU FUTUR CA SERT PROBABLEMENT A RIEN DE BLOQUER DEUX FOIS LE TRUC VU QUE CA HERITE MAIS J"AI LA FLEMME D"EFFACER
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal

    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    sigaddset(&mask, SIGUSR1);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer


    //eric je ne suis pas sur

    S_LOCALISATION *PositionChenilleG = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionChenilleG->position=4;
    PositionChenilleG->orientation=GAUCHE;

    pthread_setspecific(keySpec,(void*)PositionChenilleG);//c'est le coffre

    for(int i = 4; i > -1; i--)
    {

        struct timespec Ilest5hduMatin;
        Ilest5hduMatin.tv_sec =0;
        Ilest5hduMatin.tv_nsec = 800000000; //O,2 SECONDe 

        pthread_mutex_lock(&mutexEtatJeu);//case 0
        etatJeu.chenillesG[i].presence = NORMAL;
        etatJeu.chenillesG[i].tid = pthread_self();
        PositionChenilleG->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&Ilest5hduMatin, NULL);
        
  
        if(etatJeu.chenillesG[0].presence == NORMAL)//en gros toucher chat le truc du b en gros
        {
            Ilest5hduMatin.tv_sec =1;
            Ilest5hduMatin.tv_nsec = 500000000; //O,2 SECONDe 
            
            pthread_mutex_lock(&mutexEchec);
            echec = FLEUR_HG;
            pthread_cond_signal(&condEchec);
            pthread_mutex_unlock(&mutexEchec);
            
            pthread_mutex_lock(&mutexEtatJeu);
            etatJeu.chenillesG[i].presence = AUCUN;
            pthread_mutex_unlock(&mutexEtatJeu);

            nanosleep(&Ilest5hduMatin, NULL);
        }

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.chenillesG[i].presence = AUCUN;//clean derriere en gros passage eric
        pthread_mutex_unlock(&mutexEtatJeu);
    }

    pthread_exit(0);    

}

void *fctThreadChenilleD(void *)//commence a 4 jusuq'a 0 || ILS ONT UNE STRUCT POSITION ET ORIENTATION (VARIABLE SPÉCIFIQUE EGALEMENT) || 0.8s de move
{


    //MASQUE A MODIF //ERIC DU FUTUR CA SERT PROBABLEMENT A RIEN DE BLOQUER DEUX FOIS LE TRUC VU QUE CA HERITE MAIS J"AI LA FLEMME D"EFFACER
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal

    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    sigaddset(&mask, SIGUSR1);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer


    //eric je ne suis pas sur

    S_LOCALISATION *PositionChenilleD = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionChenilleD->position=0;
    PositionChenilleD->orientation=DROITE;

    pthread_setspecific(keySpec,(void*)PositionChenilleD);//c'est le coffre

    for(int i = 0; i < 7; i++)
    {

        struct timespec Ilest5hduMatin;
        Ilest5hduMatin.tv_sec =0;
        Ilest5hduMatin.tv_nsec = 800000000; //O,2 SECONDe 

        pthread_mutex_lock(&mutexEtatJeu);//case 0
        etatJeu.chenillesD[i].presence = NORMAL;
        etatJeu.chenillesD[i].tid = pthread_self();
        PositionChenilleD->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&Ilest5hduMatin, NULL);
        
  
        if(etatJeu.chenillesD[6].presence == NORMAL)//en gros toucher chat le truc du b en gros
        {
            Ilest5hduMatin.tv_sec =1;
            Ilest5hduMatin.tv_nsec = 500000000; //O,2 SECONDe 
            
            pthread_mutex_lock(&mutexEchec);
            echec = FLEUR_HD;
            pthread_cond_signal(&condEchec);
            pthread_mutex_unlock(&mutexEchec);
            
            pthread_mutex_lock(&mutexEtatJeu);
            etatJeu.chenillesD[i].presence = AUCUN;
            pthread_mutex_unlock(&mutexEtatJeu);

            nanosleep(&Ilest5hduMatin, NULL);
        }


        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.chenillesD[i].presence = AUCUN;//clean derriere en gros passage eric
        pthread_mutex_unlock(&mutexEtatJeu);

    }

    pthread_exit(0);    

}

void *fctThreadAraigneeG(void *)
{
    //to do masque
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    sigaddset(&mask, SIGUSR2);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer




    S_LOCALISATION *PositionAraigneeG = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionAraigneeG->orientation=GAUCHE;

    pthread_setspecific(keySpec,(void*)PositionAraigneeG);//c'est le coffre

    // for(int i=4;i>-1;i--)
    for(int i=0;i<5;i++)
    {
        struct timespec WonderFullEveryday;
        WonderFullEveryday.tv_sec =0;
        WonderFullEveryday.tv_nsec = 600000000; //O,2 SECONDe

        pthread_mutex_lock(&mutexEtatJeu);//case 0
        etatJeu.araigneesG[i].presence = NORMAL;
        etatJeu.araigneesG[i].tid = pthread_self();
        PositionAraigneeG->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&WonderFullEveryday, NULL);

        if(etatJeu.araigneesG[4].presence == NORMAL)//en gros toucher chat le truc du b en gros
        {
            WonderFullEveryday.tv_sec =1;
            WonderFullEveryday.tv_nsec = 500000000; //O,2 SECONDe 
                
            pthread_mutex_lock(&mutexEchec);
            echec = FLEUR_BG;
            pthread_cond_signal(&condEchec);
            pthread_mutex_unlock(&mutexEchec);
                
            pthread_mutex_lock(&mutexEtatJeu);
            etatJeu.araigneesG[i].presence = AUCUN;
            pthread_mutex_unlock(&mutexEtatJeu);

            nanosleep(&WonderFullEveryday, NULL);
        }


        pthread_mutex_lock(&mutexEtatJeu);
        if(etatJeu.insecticidesG[i].presence==NORMAL)//peut etre un conflit dans la variable spécifique je sais pas moi
        {
            printf("l'araigné qui bouge touche l'insecticidesG\n");;
            pthread_kill(etatJeu.insecticidesG[i].tid,SIGQUIT);// POURQUOI TU INVOQUES LE SIGURSR1 SANS AUCUNE RAISON WESH 
            // etatJeu.araigneesG[i].presence == AUCUN;//pourquoi tu refuse de  disparaitre 
            pthread_mutex_unlock(&mutexEtatJeu);//SINON CA FAIT CRASH CAR JE LIBERE PAS LE MUTEX
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutexEtatJeu);

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.araigneesG[i].presence = AUCUN;//clean derriere en gros passage eric
        pthread_mutex_unlock(&mutexEtatJeu);
    }
    pthread_exit(0);
}


void *fctThreadAraigneeD(void *)
{
    //to do masque
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer



    sigaddset(&mask, SIGUSR2);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer




    S_LOCALISATION *PositionAraigneeD = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionAraigneeD->position=4;
    PositionAraigneeD->orientation=DROITE;

    pthread_setspecific(keySpec,(void*)PositionAraigneeD);//c'est le coffre

    for(int i=4;i>-1;i--)

    {
        struct timespec WonderFullEveryday;
        WonderFullEveryday.tv_sec =0;
        WonderFullEveryday.tv_nsec = 600000000; //O,2 SECONDe

        pthread_mutex_lock(&mutexEtatJeu);//case 0
        etatJeu.araigneesD[i].presence = NORMAL;
        etatJeu.araigneesD[i].tid = pthread_self();
        PositionAraigneeD->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&WonderFullEveryday, NULL);

        if(etatJeu.araigneesD[0].presence == NORMAL)//en gros toucher chat le truc du b en gros
        {
            WonderFullEveryday.tv_sec =1;
            WonderFullEveryday.tv_nsec = 500000000; //O,2 SECONDe 
                
            pthread_mutex_lock(&mutexEchec);
            echec = FLEUR_BD;
            pthread_cond_signal(&condEchec);
            pthread_mutex_unlock(&mutexEchec);
                
            pthread_mutex_lock(&mutexEtatJeu);
            etatJeu.araigneesD[i].presence = AUCUN;
            pthread_mutex_unlock(&mutexEtatJeu);

            nanosleep(&WonderFullEveryday, NULL);
        }
        
        pthread_mutex_lock(&mutexEtatJeu);//truc qui fait crash
        for (i=1; i<=4; i++)
        {
                if(etatJeu.insecticidesD[i].presence==NORMAL)//peut etre un conflit dans la variable spécifique je sais pas moi
                {printf("%d\n",i);
                    printf("l'araigné qui bouge touche l'insecticidesD\n");;
                    pthread_kill(etatJeu.insecticidesD[i].tid,SIGQUIT);// POURQUOI TU INVOQUES LE SIGURSR1 SANS AUCUNE RAISON WESH 
                    // etatJeu.araigneesD[i].presence == AUCUN;//pourquoi tu refuse de  disparaitre 
                    pthread_mutex_unlock(&mutexEtatJeu);//SINON CA FAIT CRASH CAR JE LIBERE PAS LE MUTEX
                    pthread_exit(0);
                }
        } 
        pthread_mutex_unlock(&mutexEtatJeu);

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.araigneesD[i].presence = AUCUN;//clean derriere en gros passage eric
        pthread_mutex_unlock(&mutexEtatJeu);
    }

    pthread_exit(0);
} 

void *fctThreadInsecticideG(void *)//0.2sec
{
    //to do masque
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGUSR2);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer


    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer

    S_LOCALISATION *PositionGazGauche = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionGazGauche->position=3;
    PositionGazGauche->orientation=GAUCHE;
    pthread_setspecific(keySpec,(void*)PositionGazGauche);//c'est le coffre
    
    struct timespec Despacito;
    Despacito.tv_sec =0;
    Despacito.tv_nsec = 200000000; //O,2 SECONDe
    for(int i=3;i >-1;i--)
    {
        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesG[i].presence = NORMAL;
        etatJeu.insecticidesG[i].tid = pthread_self();
        PositionGazGauche->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&Despacito,NULL);


        pthread_mutex_lock(&mutexEtatJeu);
        if(etatJeu.araigneesG[i].presence == NORMAL)
        {
            pthread_kill(etatJeu.araigneesG[i].tid, SIGUSR2);//apparement il fause use les tid
            etatJeu.insecticidesG[i].presence = AUCUN;//vu que ca reste figer je teste cette idée pour le faire dégager
            //je test vu que ca supprime par l'arraigné
            pthread_mutex_unlock(&mutexEtatJeu);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutexEtatJeu);

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesG[i].presence = AUCUN;
        pthread_mutex_unlock(&mutexEtatJeu);
    }
    pthread_exit(0); 
}


void *fctThreadInsecticideD(void *)//wtf l'affichage  a la posi 4 dés que je lance et pourquoi j'ai un coredump apparemment c'est un délire avec le décalage en gros vecteur et posi
{//on
    printf("creation insecticidesD Debug\n");
    //to do masque
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGUSR2);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer


    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer

    S_LOCALISATION *PositionGazDroite = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionGazDroite->orientation=DROITE;
    PositionGazDroite->position=0;
    pthread_setspecific(keySpec,(void*)PositionGazDroite);//c'est le coffre
    
    struct timespec DernierChance;
    DernierChance.tv_sec =0;
    DernierChance.tv_nsec = 200000000; //O,2 SECONDe
    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesD[i].presence = NORMAL;
        etatJeu.insecticidesD[i].tid = pthread_self();
        PositionGazDroite->position=i;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&DernierChance,NULL);


        pthread_mutex_lock(&mutexEtatJeu);
        if(etatJeu.araigneesD[i].presence == NORMAL)
        {
            pthread_kill(etatJeu.araigneesD[i].tid, SIGUSR2);//apparement il fause use les tid
            etatJeu.insecticidesD[i].presence = AUCUN;//vu que ca reste figer je teste cette idée pour le faire dégager
            //je test vu que ca supprime par l'arraigné
            pthread_mutex_unlock(&mutexEtatJeu);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutexEtatJeu);

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesD[i].presence = AUCUN;
        pthread_mutex_unlock(&mutexEtatJeu);
    }
    pthread_exit(0);
}
/*void *fctThreadInsecticideD(void *)//1-4 ancienne versionen qui crashais que j'ai envoyer au prof le 1
{
    //to do masque
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    sigaddset(&mask, SIGINT);//selectionner le signal
    sigaddset(&mask, SIGUSR1);//selectionner le signal
    sigaddset(&mask, SIGUSR2);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer


    sigaddset(&mask, SIGQUIT);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer

    S_LOCALISATION *PositionGazDroite = (S_LOCALISATION*)malloc(sizeof(S_LOCALISATION));//position | direction
    PositionGazDroite->position=3;
    PositionGazDroite->orientation=GAUCHE;
    pthread_setspecific(keySpec,(void*)PositionGazDroite);//c'est le coffre
    
    struct timespec Despacito;
    Despacito.tv_sec =0;
    Despacito.tv_nsec = 200000000; //O,2 SECONDe
    for(int i=1;i <5 ;i++)
    {
        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesD[i].presence = NORMAL;
        etatJeu.insecticidesD[i].tid = pthread_self();
        PositionGazDroite->position=1;
        pthread_mutex_unlock(&mutexEtatJeu);

        nanosleep(&Despacito,NULL);

        if(etatJeu.araigneesD[i].presence == NORMAL)
        {
            pthread_kill(ThreadAraigneeG, SIGUSR2);
        }

        pthread_mutex_lock(&mutexEtatJeu);
        etatJeu.insecticidesG[i].presence = AUCUN;
        pthread_mutex_unlock(&mutexEtatJeu);
    }
    pthread_exit(0);


}*/

void destructeurVS(void *p)
{
    free(p);
}


void handlerSIGALRM(int sig)//je crash dés que je l'invoque
{
    (void)sig;//pas avoir le warning
    // fprintf(stderr,"(%d) SigAlarm envoyer\n" ,pthread_self());

    int *DelaiSpawnModif = (int *)pthread_getspecific(keySpec);//chopper la varable et la toucher dans le coffre afin c'est ce que j'ai capté

    //to entre 1.1 et 1.6sed
    *DelaiSpawnModif = 1100 + rand()% 501;

    alarm(10);//jsp si c'est propre de faire ca mais vu qu'on sort pas de la boucle je vois pas comment je pourrai le réappeler dans le thread enemie
}

void handlerSIGINT(int sig)//meme en commentant tout ca crash
{
    (void)sig;//pas avoir le warning
    fprintf(stderr,"(%d) SigInt envoyer\n" ,pthread_self());

    int *PSG = (int *)pthread_getspecific(keySpec);

    pthread_mutex_lock(&mutexEtatJeu);
    if(etatJeu.etatStanley == BAS && etatJeu.positionStanley == 2 && etatJeu.actionStanley == SPRAY)
    {
        // mettre le champ présence à AUCUN dans etatJeu.guepes et augmenter le score

        fprintf(stderr,"tu creve guepes\n");
        etatJeu.score++;//mutex ?
        etatJeu.guepes[*PSG].presence = AUCUN;
    }
    pthread_mutex_unlock(&mutexEtatJeu);
    pthread_exit(0);

}


void handlerSIGUSR1(int sig)
{
    (void)sig;
    fprintf(stderr,"(%d) SigUSR1 envoyer\n" ,pthread_self());    
    S_LOCALISATION *KohLantha = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre

    fprintf(stderr,"%d\n",KohLantha->position);
    pthread_mutex_lock(&mutexEtatJeu);
    if(KohLantha->orientation==GAUCHE)
    {
        etatJeu.chenillesG[KohLantha->position].presence= AUCUN;
        etatJeu.score++;
    }

    else if(KohLantha->orientation==DROITE)
    {
        etatJeu.chenillesD[KohLantha->position].presence= AUCUN;
        etatJeu.score++;
    }

    pthread_mutex_unlock(&mutexEtatJeu);
    pthread_exit(0);

}



void handlerSIGUSR2(int sig)//peut etre viré la condition pour faire en sorte que ca tue possiblement toute la ligne et genre faire en sorte que le sigquit clean seulement le gaz
{
    (void)sig;
    fprintf(stderr,"(%d) SigUSR2 envoyer\n" ,pthread_self());    
    S_LOCALISATION *SpiderMan = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre

    fprintf(stderr,"%d\n",SpiderMan->position);
    pthread_mutex_lock(&mutexEtatJeu);
    if(SpiderMan->orientation==GAUCHE)
    {
        if(etatJeu.araigneesG[SpiderMan->position].presence == NORMAL)//c'etait réellement ca bahahaha c'etait bien la condtion spray qui faisait qu'il crevait pas en gros eric fait des conditions pas trop précis 
        {
            etatJeu.araigneesG[SpiderMan->position].presence= AUCUN;
            etatJeu.score++;
        }

    }

    else if(SpiderMan->orientation==DROITE)
    {
        if(etatJeu.araigneesD[SpiderMan->position].presence == NORMAL)
        {
            etatJeu.araigneesD[SpiderMan->position].presence= AUCUN;
            etatJeu.score++; 
        }
    }

    pthread_mutex_unlock(&mutexEtatJeu);
    pthread_exit(0);
}



/*void handlerSIGUSR2(int sig)//peut etre viré la condition pour faire en sorte que ca tue possiblement toute la ligne et genre faire en sorte que le sigquit clean seulement le gaz
{
    (void)sig;
    fprintf(stderr,"(%d) SigUSR2 envoyer\n" ,pthread_self());    
    S_LOCALISATION *SpiderMan = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre

    fprintf(stderr,"%d\n",SpiderMan->position);
    pthread_mutex_lock(&mutexEtatJeu);
    if(SpiderMan->orientation==GAUCHE)
    {
        if(etatJeu.araigneesG[4].presence == NORMAL && etatJeu.actionStanley == SPRAY)
        {
            etatJeu.araigneesG[SpiderMan->position].presence= AUCUN;
            etatJeu.score++;
        }

    }

    else if(SpiderMan->orientation==DROITE)
    {
        if(etatJeu.araigneesD[0].presence == NORMAL && etatJeu.actionStanley == SPRAY)
        {
            etatJeu.araigneesD[SpiderMan->position].presence= AUCUN;
            etatJeu.score++; 
        }
    }

    pthread_mutex_unlock(&mutexEtatJeu);
    pthread_exit(0);
}*/


void handlerSIGQUIT(int sig)//pas incrementer score c débile edit:eric du futur j'avais mal comprjs les consignes en gros sigurs2 c'est le cas ou l'araigné a bougé pendant le gaz et ca l'avait pas kill avec quit
{
    (void)sig;
    fprintf(stderr,"(%d) Sigquit envoyer\n" ,pthread_self());    
    S_LOCALISATION *PositionGaz = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre
    printf("%d||Orientation\n",PositionGaz->orientation);
    printf("%d||||Posi\n",PositionGaz->position);

    pthread_mutex_lock(&mutexEtatJeu);
    if(PositionGaz->orientation==GAUCHE)
    {
        //TU ENTRES AU MOINS DEDANS ? nop
        printf("Big time rush\n");
/*        if(etatJeu.insecticidesG[PositionGaz->position].presence== NORMAL )
        {
            etatJeu.araigneesG[PositionGaz->position].presence== AUCUN;
            etatJeu.insecticidesG[PositionGaz->position].presence== AUCUN;
            etatJeu.score++;
        }
*/
        etatJeu.insecticidesG[PositionGaz->position].presence= AUCUN;//plus jamais je fais des copiers coller de mon code j'ai passé 1h a debug pour voir que c'etait une comparaison quej'ai faite
        etatJeu.araigneesG[PositionGaz->position].presence= AUCUN;//c'etait réellement ca 
        etatJeu.score++;
    }

    else if(PositionGaz->orientation==DROITE)
    {
        etatJeu.insecticidesD[PositionGaz->position].presence= AUCUN;//plus jamais je fais des copiers coller de mon code j'ai passé 1h a debug pour voir que c'etait une comparaison quej'ai faite
        etatJeu.araigneesD[PositionGaz->position].presence= AUCUN;//c'etait réellement ca 
        etatJeu.score++;
    }

    pthread_mutex_unlock(&mutexEtatJeu);

    pthread_exit(0);

}


/*void handlerSIGQUIT(int sig)//en gros le truc ne tue pas le spray ou reste figer
{
    (void)sig;
    fprintf(stderr,"(%d) Sigquit envoyer\n" ,pthread_self());    
    S_LOCALISATION *PositionGaz = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre
    printf("%d||Orientation\n",PositionGaz->orientation);
    printf("%d||||Posi\n",PositionGaz->position);

    pthread_mutex_lock(&mutexEtatJeu);
    if(PositionGaz->orientation==GAUCHE)
    {
        //TU ENTRES AU MOINS DEDANS ?
        printf("Big time rush\n");
        if(etatJeu.insecticidesG[PositionGaz->position].presence== NORMAL )
        {
            etatJeu.araigneesG[PositionGaz->position].presence== AUCUN;
            etatJeu.insecticidesG[PositionGaz->position].presence== AUCUN;
            etatJeu.score++;
        }

    }

    else if(PositionGaz->orientation==DROITE)
    {
        if(etatJeu.insecticidesD[PositionGaz->position].presence== NORMAL)
        {
            etatJeu.araigneesD[PositionGaz->position-1].presence= AUCUN;
            etatJeu.insecticidesD[PositionGaz->position].presence== AUCUN;
            etatJeu.score++;
        }
    }

    pthread_mutex_unlock(&mutexEtatJeu);

    pthread_exit(0);

}*/
//archive

// void handlerSIGUSR1(int sig)//la position 4 = totem immunité || 0-1 =stan0 || 2-3 stan1  marche pas mais moyen de faire mieux
// {
//     (void)sig;
//     fprintf(stderr,"(%d) SigUSR1 envoyer\n" ,pthread_self());


//     S_LOCALISATION *KohLantha = (S_LOCALISATION*)pthread_getspecific(keySpec);//c'est le coffre
//     fprintf(stderr,"Eric %d\n",KohLantha->position);
//     //je vois vraiment pas l"interet du coup 

//     pthread_mutex_lock(&mutexEtatJeu);
//     if (KohLantha->orientation==GAUCHE)//posi 0 et 1
//     {
//         printf("j'aime ton dégradé\n");
//         if(etatJeu.etatStanley == HAUT && etatJeu.positionStanley == 0 && etatJeu.actionStanley == SPRAY)
//         {
//             for(int i = 0; i < 2; i++)
//             {
//                 if(etatJeu.chenillesG[i].presence == NORMAL)
//                 {
//                 printf("Tu meurs vieille chenilleG sale en position 0\n");
//                 etatJeu.chenillesG[KohLantha->position].presence = AUCUN;
//                 etatJeu.score++;
//                 }
//             }
//         }
        
//         else if(etatJeu.etatStanley == HAUT && etatJeu.positionStanley == 1 && etatJeu.actionStanley == SPRAY)
//         {
//             for(int i = 2; i < 4; i++)
//             {
//                 if(etatJeu.chenillesG[i].presence == NORMAL)
//                 {
//                 printf("Tu meurs vieille chenilleG beaugosse en position 1\n");
//                 etatJeu.chenillesG[KohLantha->position].presence = AUCUN;
//                 etatJeu.score++;
//                 }
//             }
//         }
//     }

//     else if (KohLantha->orientation=DROITE)//posi 3 a 5
//     {
//          //pour 
//     }


//     pthread_mutex_unlock(&mutexEtatJeu);

// }
