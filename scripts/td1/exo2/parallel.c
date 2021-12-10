#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <math.h>
#define nb 18446743979220271
#define thread_count 4

void* thread_premier(void* position){
    
    int* position_pointer = (int*) position;
    int order = *position_pointer;

    int stop = (int) sqrt(nb);

    for (int j = 2 + order ; j < stop; j+=thread_count)
    {
        if(nb % j == 0){
            pthread_exit((void*) j);
        }
    }
    
    pthread_exit((void*) -1);

}


int main(int argc, char const *argv[])
{

    pthread_t* tid_array = (pthread_t*) malloc(sizeof(pthread_t)*thread_count);

    int* result_array = (int*) malloc(sizeof(int)*thread_count);

    for (int i = 0; i < thread_count; i++)
    {
        int* thread_input = malloc(sizeof(int));
        *thread_input = i;
        pthread_create(&tid_array[i], NULL, thread_premier, (void*)thread_input);
    }
    

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(tid_array[i], (void **)&result_array[i]);
        // aka there's a divisor
        if(result_array[i] != -1){
            printf("\nThe number %d has a divisor %d found by thread %d ",nb,result_array[i], i);
        }
    }
    

    return 0;
}
