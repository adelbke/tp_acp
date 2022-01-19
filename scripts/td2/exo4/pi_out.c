#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 
 
void main()
{
    float step,x,sum,pi;
    int steps, tid;
    steps=1000;
    int num;
    step = 1.0/(float)steps;
    int numthread =4;
    omp_set_num_threads(numthread);
    #pragma omp parallel private(tid, num, x) 
    {   
        tid=omp_get_thread_num();
        num=omp_get_num_threads();
 
        printf("threads num %d\n",numthread);
        printf("threads %d\n",num);
        printf("tid= %d\n",tid);
        #pragma omp for reduction(+:sum)
        for(int i= 0; i<steps; i++ )
        {
            x=(i+0.5)*step;
            sum+=4.0/(1.0+x*x);
        }
    }
    pi=step*sum;
 
    printf("pi=%.8f",pi);
    printf("\npi=%.8f",M_PI);
}