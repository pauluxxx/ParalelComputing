// MpiFirst.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "mpi.h"
#include <cstring>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
void fill_mass(int *mas, int count) {
	for (int i = 0; i < count; i++)
	{
		mas[i] = rand() * 10;
	}
}
void print_mass(int* mas, int count) {
	for (int i = 0; i < count; i++)
	{
		printf("%d, ", mas[i]);
	}
	printf("//n");
}
int main(int argc, char *argv[])
{
	int *input_mas;
	int count = 10;
	
	input_mas =(int*) malloc(sizeof(int) * count );
	printf("%d", rand());
	system("pause");
	return 0;
}
