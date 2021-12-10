#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define NUMTHREAD 2
#define RAND_MAX 50

int fib(int n){
    int x1, x2;
    if ( n <= 2 ){
        return 1;
    }

    #pragma omp task shared(n)
    x1 = fib(n - 1);

    #pragma omp task shared(n)
    x2 = fib(n - 2);

    #pragma omp taskwait
    return x1 + x2;
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

    omp_set_num_threads(2);
    
    double duration = 0.0;

    clock_t begin = clock();
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("\nfib= %d", fib(n));
        }
    }
    int out = fib(n);
    clock_t end = clock();

    duration = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(" in %f seconds", duration);
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