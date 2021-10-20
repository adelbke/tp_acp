
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>*



void *calculer_carre(void *nombre) {

    int* arguments = (int*) nombre;
    int order = arguments[0];
    int parameter = arguments[1];
    printf("\nJe suis le thread num %d et je calcule le carré de %d", order, parameter);

    free(arguments);

    int result= parameter*parameter;

    pthread_exit((void*) result);
}


int* random_array(int length){

    int* list = (int*) malloc(sizeof(int)*length);

    for(int i =0; i < length; i++){
        list[i] = rand() % 25;
    }

    return list;
}


int main(){
    int n = 8;

    int* number_array = random_array(n);
    int* result_array = (int*) malloc(sizeof(int)*n);
    
    pthread_t* tid_array = (pthread_t*) malloc(sizeof(pthread_t)*n);

    int* thread_input;

    for(int i = 0; i < n; i++){
        thread_input = (int*) malloc(sizeof(int)*2);
        thread_input[0] = i;
        thread_input[1] = number_array[i];
        
        pthread_create(&tid_array[i], NULL, calculer_carre, (void*)thread_input);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(tid_array[i], (void **)&result_array[i]);        
    }
    

    for(int i = 0; i < n; i++){
        printf("\n (%d) => %d", number_array[i], result_array[i]);
    }

    free(number_array);
    free(result_array);
    free(tid_array);

    return 0;
}

