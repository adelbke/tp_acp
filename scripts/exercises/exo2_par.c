#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define steps 100
#define thread_num 4
float i_func(float x){
    return 4.0/(1.0 + x * x);
}

int main(int argc, char const *argv[])
{
    omp_set_num_threads(thread_num);

    float start = 0, stop = 1;
    float interval_width = (stop - start) / (float) steps;

    float* results = malloc(sizeof(float) * thread_num);

    float sum= 0.0;

    #pragma omp parallel
    {
        int p_id = omp_get_thread_num();
        float result = 0.0;
        for (int i = p_id * (steps / thread_num); i < (p_id + 1) * (steps / thread_num); i++)
        {
            result += i_func(start + (interval_width * (float) i )) * interval_width;
        }
        
        #pragma omp critical
        sum += result;
    }
    
    // for (int i = 0; i < thread_num; i++)
    // {
    //     /* code */
    //     printf("\nResult[%d]= %f",i,results[i]);
    //     sum+= results[i];
    // }

    printf("\nResult: %f", sum);

    
    return 0;
}
