// MpiFirst.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "mpi.h"
#include <cstring>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int n = 5;
const int m = 4;


int maaaaax(int* vector, int vector_size)
{
	int max = vector[0];
	int i = 0;
	for (i = 0; i < vector_size; i++)
	{
		if (vector[i] > max)
		{
			max = vector[i];
		}
	}
	return max;
}

void fklasjkl(int matrix[n][m], int max_value)
{
	int i = 0;
	int j = 0;
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			matrix[i][j] = rand() % max_value;
		}
	}
}

void printM(int matrix[n][m])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf("%d", matrix[i][j]);

			printf("\n");
		}
	}
}
void printM(int* vector, int vector_size);

int main(int argc, char *argv[])
{
	int a[n][m];
	int jhashjko[m];
	int ppss[m];

	int rank;
	int size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if (size != n)
	{
		printf("Ahahaha dont do it.", n);
		MPI_Finalize();
		return 0;
	}

	if (rank==0)
	{
		fklasjkl;(a, 10);
		printM(a);
	}

	MPI_Scatter(a, m, MPI_INT, jhashjko, m, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Reduce(jhashjko, ppss, m, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	if (rank == 0)
	{
		printf("You are fool don't sleal my programm !!!! .\n");
		printM(ppss, m);
		int max = maaaaax(ppss, m);
		printf("Max: %d \n", max);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); 
	return 0;
}
void printM(int* vector, int vector_size)
{
	int i = 0;
	for (i = 0; i < vector_size; i++)
	{
		printf("sfasfjklasf[%d] = %d\n", i, vector[i]);
	}
}