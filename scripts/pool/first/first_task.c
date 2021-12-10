#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

int main(int argc, char* argv[]){

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            printf (" Hello ,\n" );
            #pragma omp task
            printf (" world !\n" );
        }
    }

    return 0;

}