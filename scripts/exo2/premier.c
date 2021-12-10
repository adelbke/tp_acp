#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const unsigned long NB= 18446743979220271;
unsigned long sqrtNB;
const unsigned long numberOfThreads = 15;
pthread_t *tid_array = NULL;


void *verifier_premier(void *positionPointer)
{
    
    unsigned long* paramNumber = (unsigned long*) positionPointer;
    unsigned long position = *paramNumber;

    printf("\n\tPosition: %lu",position);

    unsigned long rangeUnit = sqrtNB/numberOfThreads;

    for (unsigned long i = (2 * !position) +(position * rangeUnit) ; i < (position +1)* rangeUnit ; i++)
    {
        // printf("\ntesting %lu on %lu",i,NB);
        if(!(NB % i)){
            printf("\nfound divisor %lu",i);
            for (int j = 0; j < numberOfThreads; j++)
            {
                if(j != position){
                    pthread_cancel(tid_array[j]);
                }
            }
            pthread_exit((void *)i);
            
        }
    }
    
    pthread_exit((void *) 1);

}

int main(void)
{
    sqrtNB = (unsigned long) sqrt(NB);
    tid_array = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);


    int* result_array = (int*) malloc(sizeof(int)*numberOfThreads);

    unsigned long* position = NULL;

    for (unsigned long i = 0; i < numberOfThreads; i++)
    {
        position = malloc(sizeof(unsigned long));
        *position = i; 
        pthread_create(&tid_array[i], NULL, verifier_premier, (void *)position);
        // printf("\ncreating thread nb: %p with index %d",tid_array[i], i);
    }

    for (int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(tid_array[i], (void **)&result_array[i]);        
    }
    
    

}