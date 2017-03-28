// MpiFirst.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	MPI_Status Status;

	int ProcNum, ProcRank, RecvRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int myid, numprocs;
 	fprintf(stdout, "Process %d of %d\n", ProcRank, ProcNum);
	MPI_Finalize();
	return 0;
}
