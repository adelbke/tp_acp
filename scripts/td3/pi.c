#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50
#define NUMTHREAD 4 

int main(int argc, char* argv[]){

    float step, x, sum, pi;
    int i, steps;
    steps = 200.0;

    step = 1.0/(float)steps;

    float* resultArray = malloc(sizeof(float)*NUMTHREAD);

    // printf("\nwe have %d threads", omp_get_thread_num());
    omp_set_num_threads(NUMTHREAD);

    #pragma omp parallel private(x, sum)
    {
        int t_num = omp_get_thread_num();
        int start = (steps/NUMTHREAD)*t_num;
        int end = (steps/NUMTHREAD) * (t_num + 1);
        printf("\nThread %d , starts: %d , ends: %d",t_num, start, end);

        for ( i = start; i < end; i++)
        {
            x = (i + 0.5)* step;
            sum += 4.0/(1.0+x*x);
        }
        // printf("\nsum=%f",sum)

        printf("\nThread %d, sum: %f",t_num, sum);

        resultArray[t_num] = sum;
    }

    float finalSum = 0;
    for (int i = 0; i < 4; i++)
    {   
        finalSum += resultArray[i];
    }
    

    pi = step * finalSum;
    // print("pi= %f", math.pi)
    printf("\npi= %.10f", pi);

    return 0;

}