#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{

    double step, x, sum, pi;
    int i, steps;
    steps = 1000.0;

    int p[4] = { 2, 4, 6, 8 };
    int n[5] = { 200, 400, 600, 800, 1000 };

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            pi = 0, sum = 0.0;
            step = 1.0 / (double)n[k];
            omp_set_num_threads(p[j]);

            #pragma omp parallel for reduction(+:sum)
            for (int i = 0; i < n[k]; i++)
            {
                x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }

            printf("\npi for num_threads %d and steps %d is %f",p[j], n[k], sum * step);
        }
        
    }
    
    

    pi = step * sum;
    printf("\npi= %.15f", pi);

    return 0;
}