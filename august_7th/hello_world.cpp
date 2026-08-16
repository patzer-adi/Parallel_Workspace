#include<mpi.h>
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
cout<<"this should happen 1"<<endl;

MPI_Init(&argc,&argv);
int rank, size;
MPI_Status status;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
cout<<"Hello from process "<<rank << " out of "<< size << " processes..." <<endl;
MPI_Finalize();
cout<<"This should happen once"<<endl;
return 0;
}
