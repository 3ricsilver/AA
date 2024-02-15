#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>


/*
L'armement des masques est tout ca aurait pu etre fait en une seule ligne eric
Eric les truc des thread signal etait useless

*/


void handlerSIGINT(int);
void handlerSIGUSR1(int);
void *threadslave1(void*);
void *threadslave2(void*);
void *threadslave3(void*);
void *threadslave4(void*);
void *threadMaster(void*);
void cleanup(void *);
pthread_t idthreadprincipal;

int main()
{
//1
//armement signaux//

//btw le mask est locale
struct sigaction sigAct;
pthread_t idThread1,idThread2,idThread3,idThread4,idThreadMaster;
idthreadprincipal=pthread_self();//en gros c'est un sorte de getpid()

sigemptyset(&sigAct.sa_mask);
sigAct.sa_handler = handlerSIGINT;
sigAct.sa_flags = 0;
sigaction(SIGINT, &sigAct, NULL);

sigemptyset(&sigAct.sa_mask);
sigAct.sa_handler = handlerSIGUSR1;
sigAct.sa_flags = 0;
sigaction(SIGUSR1, &sigAct, NULL);

sigset_t mask;

sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_BLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_BLOCK, &mask, NULL);

//Créer des thread slave & master//

pthread_create(&idThread1, NULL, threadslave1, (void*)1);
pthread_create(&idThread2, NULL, threadslave2, (void*)2);
pthread_create(&idThread3, NULL, threadslave3, (void*)3);
pthread_create(&idThread4, NULL, threadslave4, (void*)4);
pthread_create(&idThreadMaster, NULL, threadMaster, (void*)5);
printf("Le pid du thread principale : id du thread : %ld \n", pthread_self());

	pthread_join(idThread1, NULL);//en gros un wait pour les thread eric du futur
    pthread_join(idThread2, NULL);
    pthread_join(idThread3, NULL);
    pthread_join(idThread4, NULL);

    pthread_cancel(idThreadMaster);//thread principal qui bute threadmaster

    printf("Tous les threads esclaves se sont terminés.\n");

    
    printf("th principal fin : id du thread : %ld \n", pthread_self());
    pthread_exit(NULL);//ca tue que le thread principal
    // exit(1);//ca tue tout d'un coup comme le prof avait dit en théo mais ca change rien vu qu'on les a tué avant eric du futur
}

//thread master //

void *threadMaster(void *point)
{
	pthread_cleanup_push(cleanup, NULL);//en gros pour faire apparaitre ma fonction cleanup une fois qu'il meurt

	sigset_t mask;//eric du futur tu peux faire ca en une ligne 
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_UNBLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_BLOCK, &mask, NULL);

printf("th threadMaster debut : id du thread : %ld \n", pthread_self());

printf("th threadMaster attend un signal : %ld \n");

	while(1)
	{
		pause();
	}
	
	pthread_kill (idthreadprincipal,SIGUSR1);


printf("th threadMaster fin : id du thread : %ld \n", pthread_self());

	pthread_cleanup_pop(1);//j'ai mit 1 comme ca ca excutera tj  
    pthread_exit(NULL);
}


void cleanup(void *arg) 
{
    printf("Le thread Master (%ld) se termine.\n", pthread_self());
}

//Threadslave &mmaster//

void *threadslave1(void *point)
{

	sigset_t mask;
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_BLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_UNBLOCK, &mask, NULL);

printf("th threadslave1 debut : id du thread : %ld \n", pthread_self());

printf("th threadslave1 attend un signal : %ld \n");

	pause();

	pthread_kill (idthreadprincipal,SIGUSR1);


printf("th threadslave1 fin : id du thread : %ld \n", pthread_self());

	pthread_exit(NULL);
}

void *threadslave2(void *point)
{

	sigset_t mask;
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_BLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_UNBLOCK, &mask, NULL);

printf("th threadslave2 debut : id du thread : %ld \n", pthread_self());

printf("th threadslave2 attend un signal : %ld \n");

	pause();

	pthread_kill (idthreadprincipal,SIGUSR1);


printf("th threadslave2 fin : id du thread : %ld \n", pthread_self());

	pthread_exit(NULL);
}

void *threadslave3(void *point)
{

	sigset_t mask;
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_BLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_UNBLOCK, &mask, NULL);

printf("th threadslave3 debut : id du thread : %ld \n", pthread_self());

printf("th threadslave3 attend un signal : %ld \n");

	pause();

	pthread_kill (idthreadprincipal,SIGUSR1);


printf("th threadslave3 fin : id du thread : %ld \n", pthread_self());

	pthread_exit(NULL);
}

void *threadslave4(void *point)
{

	sigset_t mask;
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigprocmask(SIG_BLOCK, &mask, NULL);

sigemptyset(&mask);
sigaddset(&mask, SIGUSR1);
sigprocmask(SIG_UNBLOCK, &mask, NULL);

printf("th threadslave4 debut : id du thread : %ld \n", pthread_self());

printf("th threadslave4 attend un signal : %ld \n");

	pause();

	pthread_kill (idthreadprincipal,SIGUSR1);


printf("th threadslave4 fin : id du thread : %ld \n", pthread_self());

	pthread_exit(NULL);
}

//Handler //

void handlerSIGINT(int)
{
        printf("handlerSIGINT : Thread %lu a recu le signal SIGINT : %ld \n", pthread_self());
        kill(getpid(),SIGUSR1);    
}

void handlerSIGUSR1(int)
{
	printf("handlerSIGUSR1 : id du thread %ld \n", pthread_self());
}


