#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMTHREAD 2
#define RAND_MAX 50

void fill_rand(int* arr, int N){
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand();
    }
}

int sum_array(int* arr, int N){
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum+=arr[i];
    }
    return sum;
}

int main(int argc, char* argv[]){

    int nb_iterations = 2;
    omp_set_num_threads(NUMTHREAD);


    int N = 50;
    int* arr = malloc(sizeof(int)*N);

    #pragma omp sections
    {
        #pragma omp section
        {
            fill_rand(arr,N);
        }

        #pragma omp barrier
        {
            sum_array(arr, N);
        }

    }



    

    return 0;

}