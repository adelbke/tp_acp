#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const unsigned long NB = 18446743979220271;
unsigned long sqrtNB;
const unsigned long numberOfThreads = 4;
pthread_t *tid_array = NULL;
const unsigned long range = 1000;
unsigned long currentStart = 2;

void *verifier_premier(void *positionPointer)
{
    // Mutex critical start
    int start = currentStart;
    assign_range();
    // Mutex critical end

    unsigned long rangeUnit = sqrtNB / numberOfThreads;

    for (unsigned long i = start; i < start + range; i++)
    {
        printf("\ntesting %lu on %lu", i, NB);
        if (!(NB % i))
        {
            printf("\nfound divisor %lu", i);
            for (int j = 0; j < numberOfThreads; j++)
            {
                if (j != position)
                {
                    pthread_cancel(tid_array[j]);
                }
            }
            pthread_exit((void *)i);
        }
    }

    pthread_exit((void *)1);
}

void assign_range(){
    currentStart = currentStart + range;
}

int main(void)
{
    sqrtNB = (unsigned long)sqrt(NB);
    tid_array = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);

    int *result_array = (int *)malloc(sizeof(int) * numberOfThreads);

    unsigned long *position = NULL;

    for (unsigned long i = 0; i < numberOfThreads; i++)
    {
        pthread_create(&tid_array[i], NULL, verifier_premier, NULL);
    }

    for (int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(tid_array[i], (void **)&result_array[i]);

    }

    for (int i = 0; i <= 1000; i++)
    {
    }
}