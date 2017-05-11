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

int find_max(int* vector, int vector_size)
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

void fill_matrix_randomly(int matrix[n][m], int max_value)
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

void write_matrix(int matrix[n][m])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
}
void write_vector(int* vector, int vector_size);

int main(int argc, char *argv[])
{
	int a[n][m];
	int receive_buffer[m];
	int partial_max[m];

	int rank;
	int size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if (size != n)
	{
		printf("Please set process count = %d and run again.", n);
		MPI_Finalize();
		return 0;
	}
	if (rank==0)
	{
		fill_matrix_randomly(a, 10);
		write_matrix(a);
	}
	MPI_Scatter(a, m, MPI_INT, receive_buffer, n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Reduce(receive_buffer, partial_max, m, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("Vector of partial max values.\n");
		write_vector(partial_max, m);

		int max = find_max(partial_max, m);
		printf("Max: %d \n", max);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); 
	return 0;
}
void write_vector(int* vector, int vector_size)
{
	int i = 0;
	for (i = 0; i < vector_size; i++)
	{
		printf("vector[%d] = %d\n", i, vector[i]);
	}
}