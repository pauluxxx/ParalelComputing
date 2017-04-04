// MpiFirst.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "mpi.h"
#include <cstring>
#include <stdio.h>
int main(int argc, char *argv[])
{
	MPI_Status Status;

	int ProcNum, ProcRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
 	fprintf(stdout, "Process %d of %d\n", ProcRank, ProcNum);
	MPI_Finalize();
	return 0;
	/*
	int myid;
	int numprocs;
	char message[30];
	int myrank;
	MPI_Status status;
	int TAG = 0;
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	int strlenth = strlen(message)+2;
	if (myrank == 0) 
	{
		for (int i = 1; i < numprocs; i++) {
			sprintf_s(message, "Hi, %d Processor!", i);
			MPI_Send(&message, 30, MPI_CHAR, i , 0, MPI_COMM_WORLD);
		
		}
		}
	else
	{
		MPI_Recv(&message, 30, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		printf("received: %s\n",message);
	}
	MPI_Finalize();*/
	//return 0;
	//int myrank, size, message;
	//int TAG = 0;
	//MPI_Status status; MPI_Init(&argc, &argv);
	//MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	//MPI_Comm_size(MPI_COMM_WORLD, &size);
	//message = myrank;
	//if ((myrank % 2) == 0)
	//{
	//	if ((myrank + 1) != size)
	//		// MPI_Send(...);
	//		MPI_Send(&message, 1, MPI_INT, myrank + 1, TAG, MPI_COMM_WORLD);
	//}
	//else
	//{
	//	if (myrank != 0)
	//		//MPI_Recv(...);
	//		MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD, &status);
	//	printf("received :%i\n", message);
	//}
	//MPI_Finalize();
	return 0;

}