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


        pthread_create(&fenetre, NULL,fctThreadFenetreGraphique,NULL);//thread quand on start le jeu
        pthread_create(&evenement, NULL,fctThreadEvenements,NULL);//thread pour lire le clavier
       pthread_create(&stan,NULL,fctThreadStanley,NULL);

        //attend la mort

        pthread_join(evenement,NULL);
    /*for(i = 0; i < 6; i++)
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
}
//eric du futur fait ca 

void* fctThreadFenetreGraphique(void*)
{
 afficherStanley(BAS, 0, NORMAL);
 afficherScore(0);

 afficherAmi(FLEUR_HG,NORMAL);
 afficherAmi(FLEUR_HD,NORMAL);
 afficherAmi(FLEUR_BG,NORMAL);
 afficherAmi(FLEUR_BD,NORMAL);
 afficherAmi(CHAT,NORMAL);
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

void *fctThreadEvenements(void *)//le truc wagner qui sert a intercepter les touches claviers ? eric du futur fait un truc pour que tu puisse le butter
{
    int event;//variable tampon

    while(1)
    {
        event=lireEvenement();
        pthread_mutex_lock(&mutexEvenement);//le truc qui permet de lock duprof
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

                    //vieille version sale moche 
                        // if(etatJeu.positionStanley == 0)
                        // {
                        //     etatJeu.actionStanley = SPRAY;
                        //      pthread_mutex_unlock(&mutexEtatJeu);
                        //      // attendre 0,2 s 
                        //      nanosleep(&tempsstan, NULL);
                        //      pthread_mutex_lock(&mutexEtatJeu);
                        //      etatJeu.actionStanley = NORMAL;
                        //      printf("spray 0\n");
                        // }
                        
                        // if(etatJeu.positionStanley == 1)
                        // {
                        //     etatJeu.actionStanley = SPRAY;
                        //      pthread_mutex_unlock(&mutexEtatJeu);
                        //      // attendre 0,2 s 
                        //      nanosleep(&tempsstan, NULL);
                        //      pthread_mutex_lock(&mutexEtatJeu);
                        //      etatJeu.actionStanley = NORMAL;
                        //      printf("spray 1\n");
                        // }

                        // if(etatJeu.positionStanley == 2)
                        // {
                        //     etatJeu.actionStanley = SPRAY;
                        //      pthread_mutex_unlock(&mutexEtatJeu);
                        //      // attendre 0,2 s 
                        //      nanosleep(&tempsstan, NULL);
                        //      pthread_mutex_lock(&mutexEtatJeu);
                        //      etatJeu.actionStanley = NORMAL;

                        //      printf("spray 2\n");
                        // }

                        // if(etatJeu.positionStanley == 3)
                        // {
                        //     etatJeu.actionStanley = SPRAY;
                        //      pthread_mutex_unlock(&mutexEtatJeu);
                        //      // attendre 0,2 s 
                        //      nanosleep(&tempsstan, NULL);
                        //      pthread_mutex_lock(&mutexEtatJeu);
                        //      etatJeu.actionStanley = NORMAL;

                        //      printf("spray 3\n");
                        // }
                        pthread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley >=0 && etatJeu.positionStanley<= 4 && etatJeu.positionStanley != 1 ) // C'est beaucoup plus beau 
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
                    // pthread_mutex_unlock(&mutexEtatJeu);     

                    // if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 0)
                    // {
                    //     etatJeu.etatStanley = ECHELLE;
                    //     etatJeu.positionStanley = 1;
                    // }

                    // if(etatJeu.etatStanley == ECHELLE && etatJeu.positionStanley == 1)
                    // {
                    //     etatJeu.etatStanley = BAS;
                    //     etatJeu.positionStanley = 1;
                    // }
                    // pthread_mutex_lock(&mutexEtatJeu);  

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
                                                
                    //version eric qui marche moitié
/*                    if(etatJeu.positionStanley == 1)
                    {
                        etatJeu.positionStanley = 0;
                    }

                    if(etatJeu.positionStanley == 0)
                    {
                        etatJeu.etatStanley = HAUT;
                        etatJeu.positionStanley = 2;
                    }*/

                    // en gros je suis débile le truc check la premiere condi si elle est juste elle passe et ce fait verif encore dans la suivante et c'est pour ca que ca skip deux a la place d'une
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
                        thread_mutex_unlock(&mutexEtatJeu);
                        if(etatJeu.positionStanley >=0 && etatJeu.positionStanley<= 5 && etatJeu.positionStanley != 2 ) // C'est beaucoup plus beau 
                        {
                            etatJeu.actionStanley = SPRAY;
                             pthread_mutex_unlock(&mutexEtatJeu);
                             // attendre 0,2 s 
                             nanosleep(&tempsstan, NULL);
                             pthread_mutex_lock(&mutexEtatJeu);
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

void *ThreadEnnemis(void *)//probablement utiliser des cases ou un vecteur  eric du futur todo
{

}