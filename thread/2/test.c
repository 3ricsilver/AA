#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
/*
 Chadric 

*/
void handler(int sig); 


void * HandlerSIGINT(int * param); 

pthread_t threadHandle[numdethread]; // Vecteur de TID

const int numdethread=4;

struct sigaction dz;

int main() 
{ 
 //armement //

  dz.sa_handler = HandlerSIGINT;
  sigemptyset(&dz.sa_mask);
  dz.sa_flags = 0;
  sigaction(SIGINT,&dz,NULL);

   sigemptyset(&mask); 
 sigaddset(&mask, SIGALRM); 
 sigprocmask(SIG_SETMASK, &mask, NULL);
 
 int *retThread[numdethread]; 
 int paramEff = 5; 
 int ret;

 ret = pthread_create(&threadHandle, NULL,(void*(*)(void*)) threadSlave, &paramEff); // en créer
 puts("Thread secondaire lance !"); 
 for (int i = 0; i < NUM_THREAD; i++) 
 {
   pthread_create(&threadHandle[i], NULL, (void*(*)(void*)) threadSlave, &thr[i]);
 }
  pause();
  
  //TESTER ET COMPARER     
  exit();
  // pthread_exit(); 

 puts("Attente de la fin du thread secondaire"); 

 ret = pthread_join(threadHandle, (void **)&retThread); // attendre la fin d'un tread
 

 printf("Valeur renvoyee par le thread secondaire = %d\n", *retThread); 
 free(retThread); 
 puts("Fin du thread principal"); 
} 

void * threadSlave (int * param) 
{ 
  pthread_t tid =pthread_self();
  printf("identite = %u\n",tid); 
  printf("J'attends un signal beaugosse\n");
  pause();
  printf("J'ai recu le signal\n")
  pthread_exit(NULL);

//    affichent leur identité (pthread_t, utilisation de pthread_self()) et un petit message 
// disant qu’il vont attendre un signal


 //pour masquer le signal
 sigemptyset(&mask); 
 sigaddset(&mask, SIGALRM); 
 sigprocmask(SIG_SETMASK, &mask, NULL);
}

void * Master (int * param) 
{ 
 while(1)
 {
  pause();
 }
}


void HandlerSIGINT(int sig)
{
  (void)sig;//pour plus avoir warning du int sig pas utilisé c'est pour toi eric du futur qui explique 


    pthread_t tid = pthread_self();
    printf("Thread %lu: Signal SIGINT reçu.\n", (unsigned long)tid);
    pthread_exit(NULL);

}