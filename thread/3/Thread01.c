#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

typedef struct
{ 
char nom[20];
int nbSecondes;
} DONNEE;

DONNEE data[] = 
{ 
"MATAGNE",15,
"WILVERS",10,
"WAGNER",17,
"QUETTIER",8,
"",0 
};

DONNEE Param;
int i=0;

void cleanup(void *arg) 
{
    printf("Le thread(%d) avec  comme Pid (%d) et Tid (%ld) se termine.\n",i, pthread_self(),getpid());
}

void* threadreveal(void *point)//je oeux pas faire plusieurs thread c dans les consignes
{
	memcpy(&Param, &data[i], sizeof(DONNEE));//vois ca comme un strcpy entre stuct eric qui relis
	pthread_cleanup_push(cleanup, NULL);//en gros pour faire apparaitre ma fonction cleanup une fois qu'il meurt
	DONNEE *param = (DONNEE *)point;
 	 struct timespec temps;//l'example du cours avec le tiret etait ce qui faisait bug 

	printf("Nom: %s", param->nom);

	temps.tv_sec = param->nbSecondes;
    temps.tv_nsec =0;
    nanosleep(&temps, NULL);

	printf("Thread Pid:%d et tid:%ld\n",getpid(),pthread_self()),

	pthread_cleanup_pop(1);//j'ai mit 1 comme ca ca excutera tj  
	
	pthread_exit(NULL);
	 return NULL;//car le compilateur aime pas sinon 
}
//to do eric du futur
/*Déclarer et initialiser correctement le mutexParam qui permettra de protéger l’accès à la 
variable globale Param. A vous de trouver les « lock » et « unlock » à mettre en place afin de 
résoudre le problème de concurrence de l’étape 1*/

int main()
{
	pthread_t idThread1[sizeof(data) / sizeof(DONNEE)];

	int nombremaxdethread ;

    for(i =  0; i < sizeof(data) / sizeof(DONNEE); i++) 
    {

        pthread_create(&idThread1[i], NULL,threadreveal, &Param);
    }
 
	for(int j =  0; j < i; j++) 
	{
        pthread_join(idThread1[j], NULL);
    }

    return 0;


}

