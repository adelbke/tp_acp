#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

int main(int argc, char* argv[]){

    float step, x, sum, pi;
    int i, steps;
    steps = 20.0;

    step = 1.0/(float)steps;

    // printf("\nwe have %d threads", omp_get_thread_num());

    #pragma omp parallel private(x)
    {
        #pragma omp for reduction(+:sum)
        for ( i = 0; i < steps; i++)
        {
            x = (i + 0.5)* step;
            sum = sum+4.0/(1.0+x*x);
        }            
    }

    pi = step * sum;
    // print("pi= %f", math.pi)
    printf("\npi= %f", pi);

    return 0;

}