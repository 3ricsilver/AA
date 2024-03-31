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
pthread_key_t keyPositionGuepe;
//

pthread_mutex_t mutexEtatJeu;
pthread_mutex_t mutexEvenement;
pthread_mutex_t mutexEchec;

pthread_t ThreadFenetreGraphique,ThreadEvenements,ThreadStanley,ThreadEnnemis,ThreadGuepe,ThreadChenilleG;

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
    Sigalarm.sa_handler = handlerSIGUSR1;
    Sigalarm.sa_flags = 0;
    sigemptyset(&Sigusr1.sa_mask);
    sigaction(SIGUSR1, &Sigalarm, NULL);




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

        pthread_cond_wait(&condEvenement,&mutexEvenement);//attend que le mutexevenement atteigne la condition

        pthread_mutex_lock(&mutexEtatJeu); 
 
        switch(etatJeu.etatStanley)
        {
            case BAS:
                switch(evenement)
                {
                    case SDLK_SPACE:

                        if(etatJeu.positionStanley == 2)
                        {
                            nanosleep(&tempsstan,NULL);
                            etatJeu.actionStanley = SPRAY;
                            for(int i = 0; i < 2; i++)
                            {
                                if(etatJeu.guepes[i].presence == NORMAL)
                                {
                                    pthread_kill(etatJeu.guepes[i].tid, SIGINT);
                                }
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
                        
                        if(etatJeu.positionStanley == 0)
                        {
                            nanosleep(&tempsstan,NULL);
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
                            nanosleep(&tempsstan,NULL);
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

        EnnemiAleatoireRandomAuPif=rand() % 4;

        //to do enlever le hardcodage du spawn

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
                pthread_create(&ThreadChenilleD, NULL, fctThreadChenilleD, NULL);
                break;
            case 4://ARAIGNEE_D
                pthread_create(&ThreadChenilleD, NULL, fctThreadChenilleD, NULL);
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



        etatJeu.guepes[i].presence = AUCUN;//clean derriere en gros passage eric

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
        
  
        if(etatJeu.chenillesG[i].presence == NORMAL && i == 0)//en gros toucher chat le truc du b en gros
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



        etatJeu.chenillesG[i].presence = AUCUN;//clean derriere en gros passage eric


    }

    pthread_exit(0);    

}

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

void handlerSIGINT(int sig)
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
//         printf("coucou\n");
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
//          //code 
//     }


//     pthread_mutex_unlock(&mutexEtatJeu);

// }