#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void *thread_function(void *var) { //le code a executer par un thread

    printf("Je suis le thread de tid :%ld, mon pid est :%d\n", pthread_self() ,getpid());
    fflush(stdout);
    // sleep(6);
    printf("Au revoir du thread de tid :%ld\n", pthread_self ()) ;
    int* ptr_attribute = (int*) var;
    int attribute = *ptr_attribute;
    int result = attribute*attribute;
    pthread_exit((void*)result); 
    // exit(0);
}


int main(){
    int i, monombre = 6;
    pthread_t tid;
    
    int nombretab[10] = {4,2,9,12,4,2,9,12,4,2};
    int resulttab[10];
    pthread_t tidtab[10];

    for(int j = 0; j < 10; j++){
        pthread_create(&tidtab[j], NULL, thread_function, (void*) &nombretab[j]);
    }


    // pthread_create(&tid, NULL, thread_function, (void*) &monombre);
    printf("\nThread principal de (pid, tid) :(%d, %ld), creation d’un thread de tid %ld \n",getpid(), pthread_self(),tid);

    for(int j = 0; j < 10; j++){
        pthread_join(tidtab[j], (void **)&resulttab[j]);
    }
    // pthread_join(tid, (void **)&i);
    for(int j = 0; j < 10; j++){
        printf("\n %d",resulttab[j]);
    }
    printf("Thread principal, la valeure de retour du thread %p est: %d\n",tid,i);
    return 0; 
}