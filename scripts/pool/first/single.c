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
            printf (" Hello ,\n" );
            printf (" world !\n" );
        }
    }

    return 0;

}