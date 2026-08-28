#include<mpi.h>
#include<iostream>
using namespace std;

int main(int argc,char* argv[])
{
    int arr[16];
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int local_size = 16/size;
    int local_arr[local_size];
    if(rank == 0)
    {
        for(int i = 0; i < 16; i++)
        {
            arr[i] = (i + 1);
        }
        for(int i = 0; i < 16; i++) cout<<"Array [" << i << "]: "<<arr[i]<<"\t";

    }
    MPI_Scatter(arr,local_size,MPI_INT,local_arr,local_size,MPI_INT,0,MPI_COMM_WORLD);
    for(int i = 0; i < local_size; i++) local_arr[i] *= 2;
    cout<<"Hello"<<endl;
    MPI_Gather(local_arr,local_size,MPI_INT,arr,local_size,MPI_INT,0,MPI_COMM_WORLD);
    if(rank == 0)
    {
        cout<<"Final array:"<<endl;

        for(int i = 0; i < 16; i++) cout<<"Array [" << i << "]: "<<arr[i]<<"\t";

    }
    MPI_Finalize();

    return 0;
}
