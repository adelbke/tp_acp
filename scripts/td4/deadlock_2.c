if (rank == 0)
{
    MPI_Ssend(&sendbuf, count, MPI_Float, 1, tag, MPI_COMM_WORLD);
    MPI_Recv(&recvbuf, count, MPI_Float, 1, tag, MPI_COMM_WORLD, &status);
}
else if (rank == 1)
{
    MPI_SRecv(&recvbuf, count, MPI_Float, 0, tag, MPI_COMM_WORLD, &status);
    MPI_Ssend(&sendbuf, count, MPI_Float, 0, tag, MPI_CMM_WORLD);
}