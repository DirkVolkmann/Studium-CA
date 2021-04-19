#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int rank = 0, size = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		char str_hello[] = "This is a longer text to test dynamic length";
		MPI_Send(str_hello, strlen(str_hello) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		printf("Rank %d sent string '%s'\n", rank, str_hello);
	}
	else if (rank > 0) {
		MPI_Status status;
		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

		int str_length=0;
		MPI_Get_count(&status, MPI_CHAR, &str_length);
		
		char* str_hello = new char[str_length];
		//char* str_hello = (char*)malloc(sizeof(char) * str_length);

		MPI_Recv(str_hello, str_length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Rank %d received string '%s' from Rank %d\n", rank, str_hello, status.MPI_SOURCE);
	}

	MPI_Finalize();
	return 0;
}