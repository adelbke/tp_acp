
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void *calculer_carre(void *nombre) {

    int* paramNumber = (int*) nombre;
    int parameter = *paramNumber;
    int result= parameter*parameter;

    pthread_exit((void*) result);
}


int main(){
    int n = 8, result;
    pthread_t tid;

    pthread_create(&tid, NULL, calculer_carre, (void*)&n);

    pthread_join(tid, (void **)&result);

    printf("\n La Valeur carrée de %d calculé dans un thread parallèle est: %d.", n, result);

    return 0;
}

