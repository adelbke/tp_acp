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

    if(rank == 0){
        // if main process
        int steps = 200;

        MPI_Bcast(&steps, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        // if other processes
        int steps;
        MPI_Bcast(&steps, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        int slice = steps / world_size;
        int start = slice * rank;
        int x, sum, step = 1.0/(float) steps;

        for (int i = start; i < start + slice; i++)
        {
            x = (i + 0.5)* step;
            sum += 4.0/(1.0+x*x);
        }
        
    }

    float* sums = malloc(sizeof(float)* (world_size-1));
    MPI_Gather(sums, world_size -1, MPI_FLOAT, sums, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for (int i = 0; i < world_size -1; i++)
        {
            printf("\n %f ,", sums[i]);
        }
        
    }

    return 0;
}
