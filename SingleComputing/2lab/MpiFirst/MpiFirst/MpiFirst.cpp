// MpiFirst.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	/*MPI_Status Status;

	int ProcNum, ProcRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
 	fprintf(stdout, "Process %d of %d\n", ProcRank, ProcNum);
	MPI_Finalize();
	return 0;*/
	int myid, numprocs = 2;
	char message[21];
	int myrank;
	MPI_Status status;
	int TAG = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	if (myrank == 0)
	{
		printf( "Hi, Second Processor!", message);
		//MPI_Send(...);
		MPI_Send(&message, 20, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	}
	else
	{
		//MPI_Recv(...);
		MPI_Recv(&message, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

		printf("received: %s\n", message);
	}
	MPI_Finalize(); return 0;
}
