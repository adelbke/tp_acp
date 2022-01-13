#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 10

int main(int argc, char const *argv[])
{
    int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];

    //  initialisation
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            a[i][j] = 1 + i + j/2;
            b[i][j] = j + 1 ;
            c[i][j] = 0;
        }
    }
    int i = 0;
    #pragma omp parallel for shared(i)
        for (i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                for (int k = 0; k < MAX; k++)
                {
                    c[i][j]+=a[i][k]*b[k][j];
                }
            }
            
        }
        
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("| %d ");
        }
        printf("\n");
    }
    
    
    return 0;
}
