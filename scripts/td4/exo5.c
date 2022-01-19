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

    // if main process
    int steps = 200;

    MPI_Bcast(&steps, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    int slice =(float)steps / (float)world_size;
    int start = slice * rank;
    float x, sum = 0.0, step = 1.0/(float) steps;

    for (int i = start; i < start + slice; i++)
    {
        x = (i + 0.5)* step;
        sum += 4.0/(1.0+x*x);
    }

    // printf("\n I'm thread %d, start: %d, slice: %d steps is %f and my sum is %f", rank, start, slice, step, sum);
    
    float sums;
    MPI_Reduce(&sum, &sums, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("\n I'm thread %d, and my final sum is %f and pi is %f", rank, sums, step * sums);
        
    }


    MPI_Finalize();

    return 0;
}
