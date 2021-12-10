#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

int main(int argc, char* argv[]){

    double total, part1, part2;

    #pragma omp parallel num_threads (2)
    {
        int tid;
        tid = omp_get_thread_num();
        if (tid == 0){
            part1 = 25;
        }
        if(tid == 1){
            part2 = 17;
        }
        #pragma omp barrier
        if(tid == 0)
        {
            total = part1 + part2;
            printf("%g \n", total);
        }
    }

    return 0;

}