#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

float i_func(float x){
    return 4.0/(1.0 + x * x);
}

int main(int argc, char const *argv[])
{
    float start = 0, stop = 1;
    float range = stop - start;
    int interval_count = 100;
    float interval_width = range / (float) interval_count;

    float result = 0.0;

    for (int i = 0; i < interval_count; i++)
    {
        float curr_start = start + (interval_width * (float) i);
        result += i_func(curr_start) * interval_width;
        printf("\nResult[%d]= %f",i,result);
        
    }

    printf("\nResult: %f", result);
    
    return 0;
}
