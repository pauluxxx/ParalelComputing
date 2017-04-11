// MpiFirst.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include "mpi.h"
#include <cstring>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
float dot(float* a, float* b, int n)
{
	float res = 0;

#pragma omp parallel for reduction(+: res)
	for (int i = 0; i < n; ++i)
	{
		res += a[i] * b[i];
	}

	return res;
}
int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	double start = MPI_Wtime();

	float *a, *b, *c;
	float *send_a = NULL, *send_b = NULL, *recv_c = NULL;
	int vector_size = 1000;
	int vector_num = 1000;
	int portion_size, remainder;
	int mpi_rank, mpi_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	if (mpi_rank == 0)
	{
		printf("List of nodes:\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);

	char node_name[MPI_MAX_PROCESSOR_NAME];
	int node_name_length;
	MPI_Get_processor_name(node_name, &node_name_length);
	printf("%s\n", node_name);
	portion_size = vector_num / mpi_size;
	remainder = vector_num - portion_size*mpi_size;

	int* send_portion_size = new int[mpi_size];
	int* send_portion_index = new int[mpi_size];
	int send_index = 0;
	for (int i = 0; i < remainder; ++i)
	{
		send_portion_size[i] = (portion_size + 1)
			*vector_size;
		send_portion_index[i] = send_index;
		send_index += send_portion_size[i];
	}
	for (int i = remainder; i < mpi_size; ++i)
	{
		send_portion_size[i] = portion_size*vector_size;
		send_portion_index[i] = send_index;
		send_index += send_portion_size[i];
	}

	int* recv_portion_size = new int[mpi_size];
	int* recv_portion_index = new int[mpi_size];
	int recv_index = 0;
	for (int i = 0; i < remainder; ++i)
	{
		recv_portion_size[i] = portion_size + 1;
		recv_portion_index[i] = recv_index;
		recv_index += recv_portion_size[i];
	}
	for (int i = remainder; i < mpi_size; ++i)
	{
		recv_portion_size[i] = portion_size;
		recv_portion_index[i] = recv_index;
		recv_index += recv_portion_size[i];
	} if (mpi_rank == 0)
	{
		send_a = new float[vector_num*vector_size];
		send_b = new float[vector_num*vector_size];
		recv_c = new float[vector_num];

		for (int i = 0; i < vector_num*vector_size; ++i)
		{
			send_a[i] = (float)rand() / RAND_MAX;
			send_b[i] = (float)rand() / RAND_MAX;
		}
	}
	a = new float[send_portion_size[mpi_rank]];
	b = new float[send_portion_size[mpi_rank]];
	c = new float[recv_portion_size[mpi_rank]];

	MPI_Scatterv(send_a, send_portion_size,
		send_portion_index, MPI_FLOAT, a,
		send_portion_size[mpi_rank], MPI_FLOAT,
		0, MPI_COMM_WORLD);
	MPI_Scatterv(send_b, send_portion_size,
		send_portion_index, MPI_FLOAT,
		b, send_portion_size[mpi_rank], MPI_FLOAT,
		0, MPI_COMM_WORLD);
	for (int i = 0; i < recv_portion_size[mpi_rank]; ++i)
	{
		c[i] = dot(a + i*vector_size,
			b + i*vector_size, vector_size);
	}
	MPI_Gatherv(c, recv_portion_size[mpi_rank], MPI_FLOAT,
		recv_c, recv_portion_size, recv_portion_index,
		MPI_FLOAT, 0, MPI_COMM_WORLD);
	if (mpi_rank == 0)
	{
		printf("Results:\n");
		for (int i = 0; i < vector_num; ++i)
		{
			//printf("%f\n", recv_c[i]);
		}

		delete[] send_a;
		delete[] send_b;
		delete[] recv_c;
	}
	delete[] a;
	delete[] b;
	delete[] c;

	delete[] send_portion_size;
	delete[] send_portion_index;
	delete[] recv_portion_size;
	delete[] recv_portion_index;
	double endTime = MPI_Wtime() - start;
	printf("%f\n", endTime*1000);
	MPI_Finalize();

	return 0;


}
