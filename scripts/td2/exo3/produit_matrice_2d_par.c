#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 10

int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];

int main(int argc, char const *argv[])
{

    //  initialisation
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            a[i][j] = 1 + i ;
            b[i][j] = j + 1 ;
            c[i][j] = 0;
        }
    }

    #pragma omp parallel for schedule(dynamic) 
    for (int i = 0; i < MAX; i++)
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
            printf("|%d",c[i][j]);
        }
        printf("\n");
    }
    
    
    return 0;
}
