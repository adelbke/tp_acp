#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// #include <sys/wait.h>
#include <sys/types.h>
#include <math.h>
#define nb 18446743979220271
#define thread_count 4

pthread_t* tid_array = NULL;

void* thread_premier(void* position){
    
    int* position_pointer = (int*) position;
    int order = *position_pointer;

    int stop = (int) sqrt(nb);

    for (int j = 2 + order * stop / thread_count ; j < 2 + (order +1 ) * stop / thread_count; j++)
    {
        if(nb % j == 0){
            printf("\nThe number %d has a divisor %d found by thread %d ",nb,j, order);
            for (int i = 0; i < thread_count; i++)
            {
                if(tid_array[i] != pthread_self()){
                    pthread_cancel(tid_array[i]);
                }
            }
            pthread_exit(0);
        }
    }
    
    pthread_exit((void*) -1);

}


int main(int argc, char const *argv[])
{

    tid_array = (pthread_t*) malloc(sizeof(pthread_t)*thread_count);

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
    }
    

    return 0;
}
