#include <stdio.h>
#include <mpich/mpi.h>

int main()
{
    MPI_Init(NULL, NULL);

    // Number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Number of current process
    int process_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    // Processor name
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // printf("Hello! - sent from process %d running on processor %s.\n\
    //     Number of processes is %d.\n\
    //     Length of proc name is %d.\n\
    //     ***********************\n",
    //        process_id, processor_name, world_size, name_len);

    MPI_Status status;
    int n = 5;

    if (process_id == 0)
    {
        // create the data
        float *data = malloc(sizeof(float) * n);

        // printf("I'm here");
        // sending the data one by one
        for (int i = 1; i < world_size; i++)
        {
            for (int j = 0; j < n; j++)
            {
                data[j] = (float) i + j * 0.1;
            }
            MPI_Ssend(data, n, MPI_FLOAT, i, 4, MPI_COMM_WORLD);
            printf("\nI'm node 0 and I just sent %d data to %d", n, i);
            fflush(stdout);
        }
    }
    else
    {
        float *data = malloc(sizeof(float) * n);

        MPI_Recv(data, n, MPI_FLOAT, 0, 4, MPI_COMM_WORLD, &status);

        printf("\n I'm process %d and I received %d of floats [", process_id, n);
        for (int i = 0; i < n; i++)
        {
            printf(" %f,", data[i]);
        }
        printf("]\n");

        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}