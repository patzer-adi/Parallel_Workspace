#include <iostream>
#include <mpi.h>
#include<random>

using namespace std;

int main(int argc, char* argv[])
{

    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(-1.0, 1.0);

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    double randomNumber = distribution(generator);
    double local_value = randomNumber * ((rank + 3) * 12) / 1000;
    double global_max;


    for(int r = 0; r < size; r++)
    {
        if(rank == r)
            cout << "Rank :" << rank << " the calc max: " << local_value<<endl;
    }

    MPI_Allreduce(&local_value, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    cout<<endl;
    cout<<endl;

    for(int r = 0; r < size; r++)
    {
        if(rank == r)
            cout << "Rank :" << rank << " the calc max: " << global_max<<endl;
    }

    MPI_Finalize();
    return 0;

}