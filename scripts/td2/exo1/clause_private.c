#include <omp.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int a = 5;

    #pragma omp parallel sections private(a)
    {
        #pragma omp section
        {
            printf("\nA avant section 1: %d",a);
            a = 15;
            printf("\nA après section 1: %d",a);
        }
        
        #pragma omp section
        {
            printf("\n Affichage: %d", a);
        }
    }
    return 0;
}
