
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void *calculer_carre(void *nombre) {
    // obtenir le pointer de type nombre depuis le pointeur type void
    int* paramNumber = (int*) nombre;
    // obtenir le nombre, et calculer le carré
    int parameter = *paramNumber;
    int result= parameter*parameter;

    pthread_exit((void*) result);
}


int main(){
    int n = 8, result;
    pthread_t tid;

    // creation du thread de calcul de carré
    pthread_create(&tid, NULL, calculer_carre, (void*)&n);

    // attente du thread de calcul de carré
    pthread_join(tid, (void **)&result);

    // affichage du resultat obtenu depuis le thread
    printf("\n La Valeur carrée de %d calculé dans un thread parallèle est: %d.", n, result);

    return 0;
}

