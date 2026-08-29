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
    int local_arr[16/size];
    if(rank == 0)
    {
    for(int i = 0; i < 16; i++)
    {
        arr[i] = (i + 1) * 10;
    }
    for(int i = 0; i < 16; i++) cout<<"Array [" << i << "]: "<<arr[i]<<"\t"<<endl;

    }
    MPI_Scatter(arr,16/size,MPI_INT,local_arr,16/size,MPI_INT,0,MPI_COMM_WORLD);
    cout<<"Hello"<<endl;
    cout<<"Processor: "<<rank<<" The array "<<endl;
    for(int i = 0; i < 16/size; i++) cout<<"Rank "<<rank<<" Array [" << i << "]: "<<local_arr[i]<<endl;
    MPI_Finalize();

    return 0;
}
