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

    ouvrirFenetreGraphique();
    pthread_t fenetre,evenement,stan;

    while(1)
    {
        pthread_create(&fenetre, NULL,fctThreadFenetreGraphique,NULL);//thread quand on start le jeu
        pthread_create(&evenement, NULL,fctThreadEvenements,NULL);//thread pour lire le clavier
        pthread_create(&stan,NULL,fctThreadStanley,NULL);
    }
    //armer et masquer ici
    //exemple


/*    for(i = 0; i < 6; i++)
    {
        afficherStanley(HAUT, i, NORMAL);
        afficherStanley(HAUT, i, SPRAY);
    }

    afficherStanley(ECHELLE, 0);
    afficherStanley(ECHELLE, 1);

    for(i = 0; i < 4; i++)
    {
        afficherStanley(BAS, i, NORMAL);
        afficherStanley(BAS, i, SPRAY);
    }

    for(i = 0; i < 5; i++)
    {
        afficherAmi(i, NORMAL);
        afficherAmi(i, TOUCHE);
    }

    for(i = 0; i < 5; i++)
        afficherChenilleG(i);

    for(i = 0; i < 7; i++)
        afficherChenilleD(i);

    for (i = 0; i < 5; i++)
    {
        afficherAraigneeG(i);
        afficherAraigneeD(i);
    }

    for(i = 0; i < 4; i++)
    {
        afficherInsecticideG(i);
        afficherInsecticideD(i + 1);
    }

    afficherGuepe(0);
    afficherGuepe(1);

    afficherEchecs(3);

    afficherScore(0);

    actualiserFenetreGraphique();
    while(1)
    {
        evenement = lireEvenement();

        switch(evenement)
        {
            case SDL_QUIT:
                exit(0);

            case SDLK_UP:
                printf("KEY_UP\n");
                break;

            case SDLK_DOWN:
                printf("KEY_DOWN\n");
                break;

            case SDLK_LEFT:
                printf("KEY_LEFT\n");
                break;

            case SDLK_RIGHT:
                printf("KEY_RIGHT\n");
                break;

            case SDLK_SPACE:
                printf("SDLK_SPACE\n");
        }
    }*/
    while(1){}
}


//eric du futur fait ca 

void* fctThreadFenetreGraphique(void*)
{
 while(true)
 {
  struct timespec temps;
  temps.tv_sec =0;
  temps.tv_nsec = 100000000; //O,1 SECONDE
 restaurerImageInterne(); // restaure l’image initiale du jeu en mémoire
 
 // afficher les personnages, le score, les échecs dans l'image interne du jeu


 afficherStanley(BAS, 0, NORMAL);
 afficherScore(0);

 afficherAmi(FLEUR_HG,NORMAL);
 afficherAmi(FLEUR_HD,NORMAL);
 afficherAmi(FLEUR_BG,NORMAL);
 afficherAmi(FLEUR_BD,NORMAL);
 afficherAmi(CHAT,NORMAL);


 actualiserFenetreGraphique(); // rendre visible l’image interne du jeu
 nanosleep(&temps, NULL); // attendre 0,1 s 
 }
 pthread_exit(0);
}

void *fctThreadEvenements(void *)//le truc wagner qui sert a intercepter les touches claviers ?
{
    int event;//variable tampon

    while(1)
    {
        event=lireEvenement();
        pthread_mutex_lock(&mutexEvenement);//le truc qui permet de lock duprof
        evenement=event;
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
    //...//apparament selon pompeo c'est masque le signal to do
    while(true)
    {
        pthread_mutex_lock(&mutexEvenement);
        //... // attendre sur condEvenement l’événement produit par le joueur DONE ?

        pthread_cond_wait(&condEvenement,&mutexEvenement);//apparemebt ce qu'il veut selon les consignes //thread puis mutex

        pthread_mutex_lock(&mutexEtatJeu); 
 
        switch(etatJeu.etatStanley)
        {
            case BAS:
                switch(evenement)
                {
                    case SDLK_SPACE:
                        if(etatJeu.positionStanley == 0)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;
                             printf("spray 0\n");
                        }
                        
                        if(etatJeu.positionStanley == 1)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;
                             printf("spray 1\n");
                        }

                        if(etatJeu.positionStanley == 2)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;

                             printf("spray 2\n");
                        }

                        if(etatJeu.positionStanley == 3)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;

                             printf("spray 3\n");
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
                        if(etatJeu.positionStanley <=3)
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
                    if(etatJeu.etatStanley == HAUT && etatJeu.positionStanley == 2)
                    {
                        etatJeu.etatStanley = ECHELLE;
                        etatJeu.positionStanley = 0;
                    }

                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 0)
                    {
                        etatJeu.etatStanley = ECHELLE;
                        etatJeu.positionStanley = 1;
                    }

                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 1)
                    {
                        etatJeu.etatStanley = BAS;
                        etatJeu.positionStanley = 1;
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
                                                

                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 1)
                    {
                        etatJeu.etatStanley = ECHELLE;
                        etatJeu.positionStanley = 0;
                    }

                    if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 0)
                    {
                        etatJeu.etatStanley = HAUT;
                        etatJeu.positionStanley = 2;
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
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;
                             printf("spray 0\n");
                        }
                        
                        if(etatJeu.positionStanley == 1)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;
                             printf("spray 1\n");
                        }

                        if(etatJeu.positionStanley == 2)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;

                             printf("spray 2\n");
                        }

                        if(etatJeu.positionStanley == 3)
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
                             etatJeu.actionStanley = NORMAL;

                             printf("spray 3\n");
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
                        if(etatJeu.positionStanley <=3)
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
                        if(etatJeu.etatStanley == HAUT && etatJeu.positionStanley == 1)
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