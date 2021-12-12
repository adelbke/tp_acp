#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// #include <sys/wait.h>
#include <sys/types.h>




void *thread_function(void *var) { //le code a executer par un thread

    // sleep(6);
    int* ptr_input = (int*) var;

    // int* ptr_attribute = (int*) var;
    int order = ptr_input[0];
    int attribute = ptr_input[1];
    printf("\n Je suis le thread num %d et je calcule le carre de %d",order, attribute);

    free(ptr_input);
    int result = attribute*attribute;
    pthread_exit((void*)result); 
    // exit(0);
}


int main(){
    int i, monombre = 6;
    pthread_t tid;
    
    int nombretab[10] = {1,2,3,4,5,6,7,8,9,10};
    int resulttab[10];
    pthread_t tidtab[10];

    int* thread_input;

    for(int j = 0; j < 10; j++){
        thread_input = (int*) malloc(sizeof(int)*2);
        thread_input[0] = j;
        thread_input[1] = nombretab[j];

        pthread_create(&tidtab[j], NULL, thread_function, (void*) thread_input);
    }


    // pthread_create(&tid, NULL, thread_function, (void*) &monombre);
    // printf("\nThread principal de (pid, tid) :(%d, %ld), creation d’un thread de tid %ld \n",getpid(), pthread_self(),tid);

    for(int j = 0; j < 10; j++){
        pthread_join(tidtab[j], (void **)&resulttab[j]);
    }
    // pthread_join(tid, (void **)&i);
    for(int j = 0; j < 10; j++){
        printf("\n %d",resulttab[j]);
    }
    // printf("Thread principal, la valeure de retour du thread %p est: %d\n",tid,i);
    return 0; 
}

