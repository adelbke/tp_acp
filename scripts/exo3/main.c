#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    // omp_set_num_threads(32);
    // #pragma omp parallel
    // {
    //     printf("Hello world ... from thread = %d\n", omp_get_thread_num());
    // }
    int val = 55;
    omp_set_num_threads(2);
    #pragma omp parallel firstprivate(val)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                val = val + 1;
                printf("\nHello %d\n", val);

            }
            
            #pragma omp section
            printf("\nHello %d", val);
            
            #pragma omp section
            printf("\nHello from section 3");
        }
    }

}