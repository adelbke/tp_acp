#include <stdio.h>
#include <stdlib.h>
#include <mpich/mpi.h>

int main(int argc, char const *argv[])
{
    int m = 0, n = 0;
    float l, r, t, b;

    // initializing parallelization
    MPI_Init(NULL, NULL);

    int world_size, rank, name_len;
    char processor_name[30];

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);

    if (rank == 0)
    {
        // retreiving the lengths of the matrix
        printf("\nDonner le nombre des lignes de la matrice A: ");
        fflush(stdout);
        scanf("%d", &m);

        printf("\nDonner le nombre des colonnes de la matrice A: ");
        scanf("%d", &n);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    float a[m][n];

    if (rank == 0)
    {
        // acquiring the boundary conditions
        printf("Enter boundary conditions:les valeures de la température sur les bords \n");
        printf("\tValue on left side: ");
        scanf("%f", &l);
        printf("\tValue on right side: ");
        scanf("%f", &r);
        printf("\tValue on top side: ");
        scanf("%f", &t);
        printf("\tValue on bottom side: ");
        scanf("%f", &b);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i][j] = 0;
            }
        }

        //assigning boundary values
        for (int i = 0; i < m; i++)
        {
            a[i][0] = b;
            a[i][n - 1] = t;
        }

        for (int i = 0; i < n; i++)
        {
            a[0][i] = l;
            a[m - 1][i] = r;
        }
    }

    MPI_Datatype uneLigne;

    MPI_Type_vector(m, 1, 0, MPI_FLOAT, &uneLigne);
    MPI_Type_commit(&uneLigne);

    float lines[3][n];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            lines[i][j] = 0;
        }
    }

    MPI_Status status;
    if (rank == 0)
    {
        for (int i = 1; i < world_size; i++)
        {
            MPI_Send(&a[i - 1], m * 3, uneLigne, i, 5, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(lines, m * 3, uneLigne, 0, 5, MPI_COMM_WORLD, &status);
    }

    // can't be done with scatter https://stackoverflow.com/a/25815895
    // MPI_Scatter(a, m*3, uneLigne, lines, m*3, uneLigne, 0, MPI_COMM_WORLD);

    // sleep(2);
    // if (rank == 3)
    // {
    //     printf("process %d has: \n", rank);
    //     for (int i = 0; i < 3; i++)
    //     {
    //         for (int j = 0; j < m; j++)
    //         {
    //             printf("%f ", lines[i][j]);
    //         }
    //         printf("\n");
    //     }
    //     fflush(stdout);
    // }

    // process the three lines
    if (rank != 0)
    {
        float newLine[n];
        newLine[0] = lines[1][0];
        newLine[n - 1] = lines[1][n - 1];
        for (int i = 1; i < m - 1; i++)
        {
            newLine[i] = (lines[0][i] + lines[2][i] + lines[1][i - 1] + lines[1][i + 1]) / 4;
        }
        MPI_Send(newLine, m, uneLigne, 0, 6, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < world_size; i++)
        {
            MPI_Recv(&a[i], m, uneLigne, i, 6, MPI_COMM_WORLD, &status);
        }
        sleep(2);
        printf("process %d has: \n", rank);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%f ", a[i][j]);
            }
            printf("\n");
        }
        fflush(stdout);
    }

    return 0;
}
