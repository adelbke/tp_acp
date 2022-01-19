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

    if (process_id == 0)
    {
        int data = 15;

        MPI_Ssend(&data, 1, MPI_INT, 1, 4, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, world_size - 1, 4, MPI_COMM_WORLD, &status);
        printf("\nReturn to Sender with value %d\n", data);
        fflush(stdout);
    }
    else
    {
        int data;
        MPI_Recv(&data, 1, MPI_INT, process_id - 1, 4, MPI_COMM_WORLD, &status);
        if (process_id + 1 < world_size)
        {
            printf("\nI am %d Received value %d from %d and passing to %d", process_id, data, process_id - 1, process_id + 1);
            fflush(stdout);
            MPI_Ssend(&data, 1, MPI_INT, process_id + 1, 4, MPI_COMM_WORLD);
        }
        else
        {
            printf("\nI am %d The last and I am passing it back to 0", process_id);
            fflush(stdout);
            // int d = 5;
            MPI_Ssend(&data, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}