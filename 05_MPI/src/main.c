#include <stdio.h>
#include <mpi.h>

int main(int nargs, char** args)
{
    int size, my_rank, flag;
    MPI_Status status;

    MPI_Init(&nargs, &args);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank > 0)
    {
        MPI_Recv(&flag, 1, MPI_INT, my_rank - 1, 100, MPI_COMM_WORLD, &status);
    }
    printf("Hello world, I've rank %d out of %d procs.\n", my_rank, size);
    if (my_rank < size - 1)
    {
        MPI_Send(&my_rank, 1, MPI_INT, my_rank + 1, 100, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
