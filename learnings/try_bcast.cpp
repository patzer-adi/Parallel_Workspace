#include<iostream>
#include<mpi.h>
using namespace std;


int main(int argc, char* argv[])
{

    int x;
    MPI_Init(&argc,&argv);
    int rank, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0)
    {
        x = 42;
    }
    MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout<<"hello"<<endl;
    cout<<"Process: "<<rank<<" has value "<<x<<" received"<<endl;
    MPI_Finalize();
    return 0;
}
