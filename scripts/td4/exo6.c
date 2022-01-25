#include <mpich/mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 5
#define COL_SIZE 5

int main(int argc, char const *argv[])
{
    MPI_Init(NULL, NULL);

    int world_size, rank, name_len;
    char processor_name[30];

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);

    int B[LINE_SIZE][COL_SIZE];
    int A[LINE_SIZE][COL_SIZE];
    int line[LINE_SIZE];

    if (rank == 0)
    {
        // if main process
        for (int i = 0; i < LINE_SIZE; i++)
        {
            for (int j = 0; j < COL_SIZE; j++)
            {
                A[i][j] = j;
                B[i][j] = A[i][j];
            }
        }
    }

    MPI_Bcast(&B, LINE_SIZE * COL_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(&A, LINE_SIZE, MPI_INT, &line, LINE_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // if (rank == 1)
    // {
    //     for (int i = 0; i < 3; i++)
    //     {
    //         for (int j = 0; j < 3; j++)
    //         {
    //             printf("%d,", B[i][j]);
    //         }
    //         printf("\n ");
    //     }
    // }

    // affichage des données de chaque thread
    // sleep(3);

    // printf("\nProcessus %d a reçu %d donnée [ ", rank, 3);
    // for (int i = 0; i < LINE_SIZE; i++)
    // {
    //     printf("%d, ", line[i]);
    // }
    // printf("]");
    // printf("process  %d has B: \n",rank);
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         printf("%d ,",B[i][j]);
    //     }
    //     printf("\n");
    // }
    

    int result[LINE_SIZE] = {0 , 0 , 0};

    
    for (int i = 0; i < COL_SIZE; i++)
    {
        for (int j = 0; j < LINE_SIZE; j++)
        {
            result[i] += line[j] * B[j][i];
            // printf("result[%d]=%d * %d \n",i,line[j],B[j][rank]);
        }        
    }

    // sleep(2);    
    // printf("Processus %d a calculé %d donnée [ ", rank, LINE_SIZE);
    // for (int i = 0; i < LINE_SIZE; i++)
    // {
    //     printf("%d, ", result[i]);
    // }
    // printf("]\n");

    // sleep(2);
    int matrix_output[LINE_SIZE][COL_SIZE];
    MPI_Gather(result, LINE_SIZE, MPI_INT, matrix_output, LINE_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("\n Voici la matrice finale affiché depuis rank=%d:\n ",rank);
        for (int i = 0; i < LINE_SIZE; i++)
        {
            for (int j = 0; j < COL_SIZE; j++)
            {
                printf("%d, ", matrix_output[i][j]);
            }
            printf("\n ");
        }
        
    }

    MPI_Finalize();
    return 0;
}
