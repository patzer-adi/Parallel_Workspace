#include<mpi.h>
#include<iostream>
using namespace std;

int main(int argc,char* argv[])
{
    int arr[16];
    int rank, size;
    int global_sum = 0;
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
    cout << endl;

    MPI_Scatter(arr,local_size,MPI_INT,local_arr,local_size,MPI_INT,0,MPI_COMM_WORLD);

    for(int r = 0; r < size; r++)
    {
    if(rank == r)
    {
        cout<<"Rank "<<rank<<" : ";
        for(int i = 0; i < local_size; i++)
        {
            cout<< local_arr[i];
            if(i != local_size - 1) cout<<" + ";
        }
        cout<<endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    }
    int local_sum = 0;
    for(int i = 0; i < local_size; i++){ local_sum += local_arr[i]; }

    //cout<<"Hello"<<endl;

    MPI_Reduce(&local_sum, &global_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){cout << "Final sum: "<<global_sum<<endl;}
    MPI_Finalize();

    return 0;
}
