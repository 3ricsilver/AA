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

pthread_mutex_t mutexEtatJeu;
pthread_mutex_t mutexEvenement;
pthread_mutex_t mutexEchec;

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
     { BAS, 1, NORMAL,
       { NORMAL, NORMAL, NORMAL, NORMAL, NORMAL },
       { { AUCUN, 0 }, { AUCUN, 0 } },
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

    struct sigaction Sigalarm;
    Sigalarm.sa_handler = handlerSIGALRM;
    Sigalarm.sa_flags = 0;
    sigemptyset(&Sigalarm.sa_mask);
    sigaction(SIGALRM, &Sigalarm, NULL);


    pthread_mutex_init(&mutexEtatJeu,NULL);
    pthread_mutex_init(&mutexEvenement,NULL);
    pthread_mutex_init(&mutexEchec,NULL);

    pthread_cond_init(&condEvenement,NULL);
    pthread_cond_init(&condEchec,NULL);

    pthread_key_create(&keySpec,destructeurVS);
/*todo faire une fonction free pour libérer la mémoire*/
    
    //truc pour generer un chiffre au pif en gros la seed si tu as la flemme de relire
    srand(time(NULL));

    ouvrirFenetreGraphique();
    
    pthread_t fenetre,evenement,stan,EnemieMobChezPasQuoi;


    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

    pthread_create(&fenetre, NULL,fctThreadFenetreGraphique,NULL);//thread quand on start le jeu
    pthread_create(&evenement, NULL,fctThreadEvenements,NULL);//thread pour lire le clavier
    pthread_create(&stan,NULL,fctThreadStanley,NULL);
    pthread_create(&EnemieMobChezPasQuoi,NULL,fctThreadEnnemis,NULL);

        //attend la mort

        pthread_join(evenement,NULL);

}
//eric du futur fait ca 

void* fctThreadFenetreGraphique(void*)
{

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

 while(true)
 {
  struct timespec temps;
  temps.tv_sec =0;
  temps.tv_nsec = 100000000; //O,1 SECONDE
 restaurerImageInterne(); // restaure l’image initiale du jeu en mémoire
 
 // afficher les personnages, le score, les échecs dans l'image interne du jeu



 afficherStanley(etatJeu.etatStanley,etatJeu.positionStanley,etatJeu.actionStanley);

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
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

    while(true)
    {
        pthread_mutex_lock(&mutexEvenement);

        pthread_cond_wait(&condEvenement,&mutexEvenement);//attend que le mutexevenement atteigne la condition

        pthread_mutex_lock(&mutexEtatJeu); 
 
        switch(etatJeu.etatStanley)
        {
            case BAS:
                switch(evenement)
                {
                    case SDLK_SPACE:

                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley >=0 && etatJeu.positionStanley<= 4 && etatJeu.positionStanley != 1 ) 
                        {
                            etatJeu.actionStanley = SPRAY;
                             
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             
                             etatJeu.actionStanley = NORMAL;

                             printf("spray bas %d\n",etatJeu.positionStanley);
                        }
                        pthread_mutex_lock(&mutexEtatJeu);


                        break;
                     case SDLK_LEFT:
                        
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley > 0)
                        {
                            etatJeu.positionStanley--;
                            printf("GAUCHE bas tu es la\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;
                    
                    case SDLK_RIGHT:
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley <3)
                        {
                            etatJeu.positionStanley++;
                            printf("droite bas\n");
                        }
                        else
                        {
                            printf("tu fais une eric la tu peux pas aller plus loin que ca\n");
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;

                    case SDLK_UP:
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.etatStanley == BAS && etatJeu.positionStanley == 1)
                        {
                            etatJeu.etatStanley = ECHELLE;
                            etatJeu.positionStanley = 1;
                        }

                        pthread_mutex_lock(&mutexEtatJeu);
                        break;

                }
                break;
        
            case ECHELLE:
                switch(evenement)
                {
                    case SDLK_DOWN:

                    pthread_mutex_unlock(&mutexEtatJeu);  
                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley < 1)
                    {
                        etatJeu.positionStanley++;
                    }

                    else if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 1)
                    {
                        etatJeu.positionStanley=1;
                        etatJeu.etatStanley = BAS;
                    }
                    pthread_mutex_lock(&mutexEtatJeu);

                    break;

                    case SDLK_UP:       
                    pthread_mutex_unlock(&mutexEtatJeu);
                                                
                    if (etatJeu .positionStanley==1)
                        etatJeu.positionStanley = 0;

                    else if(etatJeu.positionStanley ==0)
                    {
                            etatJeu.positionStanley = 2;
                            etatJeu.etatStanley =HAUT ;
                    }
                    pthread_mutex_lock(&mutexEtatJeu);
                    break;
                 
                }
                break;
        
        case HAUT:
        switch(evenement)
                {
                    case SDLK_SPACE:
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley >=0 && etatJeu.positionStanley<= 5 && etatJeu.positionStanley != 2 ) // C'est beaucoup plus beau 
                        {
                            etatJeu.actionStanley = SPRAY;
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             etatJeu.actionStanley = NORMAL;

                             printf("spray bas %d\n",etatJeu.positionStanley);
                        }
                        pthread_mutex_lock(&mutexEtatJeu);

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
    //to do un truc pour recevoir le signal unblock
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);// bloquer
            
    alarm(10);//invoquer le saint sig

    int EnnemiAleatoireRandomAuPif;//faire srand

    //son timer bizzare faut le visualier comme un coffre avec une clée (utilisation du malloc) en gros eric du futur qui relit c'est setspecific c'est comme un coffre avec une clé pour accéder au truc
    int *TimerEnnemieCooldown = (int*)malloc(sizeof(int));//son timer initiale
    *TimerEnnemieCooldown=1600;
    pthread_setspecific(keySpec,(void*)TimerEnnemieCooldown);//c'est le coffre

    while(1)
    {

        EnnemiAleatoireRandomAuPif=rand() % 4;
        fprintf(stderr,"Enemies %d spawn \n",EnnemiAleatoireRandomAuPif);


        //to do mettre les threads de ces enemies
        switch(EnnemiAleatoireRandomAuPif)
        {
            case 0://GUEPE
                break;
            case 1://CHENILLE_G
                // pthread_create(&Guepes, NULL, fctThreadGuepe, NULL);
                break;
            case 2://CHENILLE_D
                break;
            case 3://ARAIGNEE_G
                break;
            case 4://ARAIGNEE_D
                break;
        }

        struct timespec Lagalere;
        Lagalere.tv_sec = *TimerEnnemieCooldown / 1000; // Seconde donc je vais chopper les 1 secondes car ca va arrondir 1.6 a 1
        Lagalere.tv_nsec = (*TimerEnnemieCooldown % 1000) * 1000000; // 0.6 qui nous faut

        //pour pas spam les mobs
        nanosleep(&Lagalere, NULL);
        //pour test a enlever voir si ca fait bien changer le 1.6 s
        fprintf(stderr,"Je varie bro %d\n",*TimerEnnemieCooldown);//pourquoi ca affiche un truc bizzare

        /*free(TimerEnnemieCooldown);//destructeur*/
    }

}

//to do faire un sig int

void *fctThreadGuepe(void *)
{
    //masque ??
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);//selectionner le signal
    pthread_sigmask(SIG_BLOCK, &mask, NULL);// bloquer

    for(int Kaaris=0; Kaaris < 2; Kaaris++)
    {

    }
        
    pthread_exit(0);
}

void destructeurVS(void *p)
{
    free(p);
    fprintf(stderr,"Destruceur Vs");
}


void handlerSIGALRM(int sig)//je crash dés que je l'invoque
{
    (void)sig;//pas avoir le warning
    fprintf(stderr,"(%d) SigAlarm envoyer\n" ,pthread_self());

    int *DelaiSpawnModif = (int *)pthread_getspecific(keySpec);//chopper la varable et la toucher dans le coffre afin c'est ce que j'ai capté

    //to entre 1.1 et 1.6sed
    *DelaiSpawnModif = 1100 + rand()% 501;

    alarm(10);//jsp si c'est propre de faire ca mais vu qu'on sort pas de la boucle je vois pas comment je pourrai le réappeler dans le thread enemie
}

void handlerSIGINT
{
    (void)sig;//pas avoir le warning
    fprintf(stderr,"(%d) SigInt envoyer\n" ,pthread_self());
    
}