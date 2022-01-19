#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMTHREAD 4 

int main(int argc, char* argv[]){

    double step, x, sum, pi;
    int i, steps;
    steps = 1000.0;

    step = 1.0/(double)steps;

    #pragma omp parallel for private(x) reduction(+:sum)
    for (int i = 0; i < steps; i++)
    {
        x = (i + 0.5)* step;
        sum += 4.0/(1.0+x*x);
    }


    pi = step * sum;
    printf("\npi= %.15f", pi);

    return 0;
}