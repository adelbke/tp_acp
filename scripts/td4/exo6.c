#include <mpich/mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    MPI_Init(NULL, NULL);
    
    int world_size, rank, name_len;
    char processor_name[30];

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);

    int B[10][5];
    int A[5][10];
    int line[10];


    if(rank == 0){
        // if main process
        int steps = 200;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                A[i][j] = i+j;
                B[i][j] = A[i][j] - 2;
            }
            
        }
        
        MPI_Bcast(&B, 10 * 5, MPI_INT, 0, MPI_COMM_WORLD);


    }else{
        // if other processes

        MPI_Bcast(&B, 10 * 5, MPI_INT, 0, MPI_COMM_WORLD);
        
        printf("\n received B ");        
        
    }

    MPI_Scatter(&A, 10, MPI_INT, &line, 10, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank != 0){
        printf("\nProcessus %d a reçu %d donnée [ ", rank, 10);
        for (int i = 0; i < 10; i++)
        {
            printf("%d, ",line[i]);
        }
        printf("]");
    }


    MPI_Finalize();
    return 0;
}
