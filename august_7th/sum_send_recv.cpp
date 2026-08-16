#include<mpi.h>
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{

	int n=100;
	int arr[n];

	MPI_Init(&argc,&argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int offset = n/size;
	
	if(rank == 0)
	{

		for(int i = 0; i < n; i++)
		{
			arr[i] = i * 2;
		}
		
		int global_sum = 0;

		for(int i = 0; i < n; i++)
		{
			global_sum += arr[i];
		}

		offset = n / size;
		for(int i = 1 ; i < size; i++)
		{
			MPI_Send(&arr[offset] , n/size, MPI_INT, i, 0, MPI_COMM_WORLD);
			offset = offset + n / size;	
		}
		

		int local_sum;		
		for(int i = 1 ; i < size; i++)
		{
			MPI_Recv(&local_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			global_sum += local_sum;
		}
		cout<< "Global sum = " << global_sum << endl;		
	}

	else
	{
		int recv[n / size];
		MPI_Recv(recv , n / size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		int local_sum = 0;		
		for(int i = 0; i < n/size; i++)
		{	
			local_sum += recv[i];
		}
		MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

return 0;
}
