#include <mpi.h>
#include <iostream>
using namespace std;
double function_f(double x)
{
    double x_return = 1.0 / (x * x + 1.0);
    return x_return;
}
int main(int argc, char* argv[])
{
    int rank, size;

    double a = 1.0;
    double b = 2.0;
    int n = 1023;
    double h = (b - a) / n;
    double first_val = function_f(a);
    double last_val = function_f(b);
    double local_sum = 0.0;
    double global_sum = 0.0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int interior_points = n - 1;
    int step = interior_points / size;
    int remainder = interior_points % size;
    int start = rank * (step + 1);
    int end = start + step;
    for (int i = start; i <= end; i++)
    {
        double x = a + i * h;
        double y = function_f(x);

        if (i % 3 == 0)
        {
            local_sum += 2.0 * y;
        }
        else
        {
            local_sum += 3.0 * y;
        }
    }
    MPI_Reduce(
        &local_sum,
        &global_sum,
        1,
        MPI_DOUBLE,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );
    if (rank == 0)
    {
        global_sum = first_val + global_sum + last_val;
        double final_integral = (3.0 * h / 8.0) * global_sum;
        cout << "Final Integral = " << final_integral << endl;
    }
    MPI_Finalize();
    return 0;
}
