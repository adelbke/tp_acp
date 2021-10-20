#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


/* 
Les messages du thread ne s'ont pas affichés car le thread principal a terminé suffisamment rapidement avant que le
thread crée puisse afficher les messages nécessaires

*/

void *thread_function(void *var) { //le code a executer par un thread

    printf("Je suis le thread de tid :%p, mon pid est :%d\n", pthread_self () ,getpid()) ;
    sleep(6);
    printf("Au revoir du thread de tid :%p\n", pthread_self ()) ;
    pthread_exit((void*)42); 

}

int main(){
    int i;
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);
    printf("Thread principal de (pid, tid) :(%d, %p), creation d’un thread de tid %p \n",getpid(), pthread_self(),tid);
    //pthread_join(tid, (void **)&i);
    //printf("Thread principal, la valeure de retour du thread %p est: %d\n",tid,i);
return 0; }