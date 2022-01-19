if (rank == 0)
{
    MPI_Recv(&recvbuf, count, MPI_Float, 1, tag, MPI_COMM_WORLD,&status);
    MPI_Send(&sendbuf, count, MPI_Float, 1, tag, MPI_COMM_WORLD);
}
else if (rank == 1)
{
    MPI_Send(&sendbuf, count, MPI_Float, 0, tag, MPI_CMM_WORLD, &status);
    MPI_Recv(&recvbuf, count, MPI_Float, 0, tag, MPI_COMM_WORLD, &status);
}
