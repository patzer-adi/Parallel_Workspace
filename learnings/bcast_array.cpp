#include<iostream>
#include<mpi.h>
using namespace std;

int main(int argc,char* argv[])
{
    int arr[10];
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank == 0)
    {
    for(int i = 0; i < 10; i++)
    {
        arr[i] = (i + 1) * 2;
    }
    }
    MPI_Bcast(&arr,10,MPI_INT,0,MPI_COMM_WORLD);
    cout<<"Hello"<<endl;
    cout<<"Process: "<< rank << " The array :" << arr<< " recevied."<<endl;
    for(int i = 0; i < 10; i++)
    {
       cout<< arr[i]<< "\t";
    }
    MPI_Finalize();
    return 0;
}
