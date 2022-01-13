#include <omp.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    // Two threads
    // omp_set_num_threads(2);
    // Four threads
    omp_set_num_threads(4);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("\n Hello %d",omp_get_thread_num());
        }

        #pragma omp section
        {
            printf("\n World %d", omp_get_thread_num());
        }
    }
    return 0;
}
