#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define NUMTHREAD 2
#define RAND_MAX 50


int fib(int n){
    if(n <= 2){
        return 1;
    }else{
        int first, second;
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                first = fib(n-1);

                #pragma omp section
                second = fib(n-2);

            }
            // #pragma omp barrier

        }

        return first + second;
    }
}


int fibseq(int n){
    if(n <= 2){
        return 1;
    }else{
        return fib(n-1) + fib(n-2);
    }
}

int main(int argc, char* argv[]){
    
    int n = 35;

    // float start, end;
    
    double duration = 0.0;

    clock_t begin = clock();
    int out = fib(n);
    clock_t end = clock();

    duration = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nFib(%d) = %d in %f seconds",n,out, duration);
    fflush(stdout);

    clock_t begin2 = clock();
    out = fibseq(n);
    clock_t end2 = clock();
    duration = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("\nFibseq(%d) = %d in %f seconds",n,out, duration);
    // compute fibonacci of n
    // F(n + k) = F(n + 1) * F(K) + F(n) * F(k - 1)

    return 0;
}