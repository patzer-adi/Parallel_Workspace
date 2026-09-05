#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[])
{

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_value = rank + 1;
    int global_sum = 0;



    MPI_Allreduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for(int r = 0; r < size; r++)
    {
        if(rank == r)
            cout << "Rank :" << rank << " the calc sum: " << global_sum<<endl;
    }

    MPI_Finalize();
    return 0;

}