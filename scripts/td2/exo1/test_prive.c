#include <omp.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int a = 5;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // with critical or not the output is the same, misunderstanding ?
            #pragma omp critical
            {
                a = 15;
            }
        }
        
        #pragma omp section
        {
            printf("\n Affichage: %d", a);
        }
    }
    return 0;
}
