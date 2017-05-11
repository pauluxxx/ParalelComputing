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

void fill_matrix_randomly(int **mas, int count) {
	
}

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
	int partial_min[m];

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

/*

    


/*And here is the output.
$ mpiexec - n 5 . / main
8   1   3   9
1   0   3   1
4   9   5   5
1   7   4   9
8   5   7   4
Vector of partial max values.
vector[0] = 9
vector[1] = 8
vector[2] = 5
vector[3] = 9
vector[4] = 16
Vector of partial min values.
vector[0] = -1
vector[1] = -1
vector[2] = -1
vector[3] = -1
vector[4] = 1
Matrix boundaries = [-1..16]
Where am I wrong ? What I should change ? I spend the whole day trying to find solution.
parallel - processing mpi
share
edited Aug 12 '13 at 16:10 

Wesley Bland
5, 73732344
asked Dec 13 '12 at 15:32 

Pavel Shchegolevatykh
57631126

add a comment
1 Answer
active
oldest
votes
up vote
2
down vote
accepted
Your matrix is n rows by m columns.When you distribute this matrix to n processes, each process has to process m elements, but instead you use a count of n in all your vector calls.You should pass a length of m in :
the MPI_Scatter call;
both MPI_Reduce calls;
both write_vector calls;
the find_max and find_min calls.
Note that you have correctly declared receive_buffer, partial_max, partial_min to be of m elements.
share
answered Dec 13 '12 at 15:54 

Hristo Iliev
47.4k468111



Thank you so much!It works fine now.– Pavel Shchegolevatykh Dec 13 '12 at 16:34 
add a comment
Your Answer



















Sign up or log in
Sign up using Google
Sign up using Facebook
Sign up using Email and Password
Post as a guest
Name

Email


By posting your answer, you agree to the privacy policy and terms of service.
Not the answer you're looking for? Browse other questions tagged parallel-processing mpi or ask your own question. 
asked
4 years, 4 months ago
viewed
2130 times
active
3 years, 9 months ago
Blog


Introducing Stack Overflow Trends


Podcast #108: Welcome Back Joel!


Work from anywhere
Software Engineer
DatadogNew York, NY
Remote
gopython
Java Chief Software Architect - $100K
CrossoverNo office location
Remote
javacloud
Related
21
What is the best MPI implementation
3
MPI buffered send / receive order
2
MPI double rings, max, min and average
1
Hiding communication in Matrix Vector Product with MPI
- 2
How can I send the rows of a matrix to another process with mpi ?
4
MPI : shared variable value for all processors
	0
	MPI Parallelization time consumption
	4
	How can I check receive message in MPI
	4
	understanding MPI send differences
	- 1
	Blocking MPI calls
	Hot Network Questions
	Sorting STDIN by length and number of nonblanks in a Bash Script
	What are the default text editors in different flavours of Ubuntu ?
	Economy without inflation
	Normalizable wavefunction that does not vanish at infinity
	How long before robin no longer needs the nest on my porch ?
	When performing for money, do musicians have to buy special sheet music for copyright purposes ?
	Why would all races simultaneously need to find new homeland
	Is it unprofessional to simply announce your absence in case of a family death ?
	Download a file from the Internet
	When galaxies collide, what happens to dark v.light matter ?
	Is this a M.O.D.O.K.reference ?
	Reasons not to use a 741 op - amp ?
	What is the equivalent of Bash's cat -n in PowerShell? 
	Replace Line Breaks(Multiple count as 1) in a string
	Why do the Rohirrim apparently find the H - word offensive ?
	Where should the brake calipers grasp the rotor ?
	Why 'photoshop' passport photos ?
	What ext4 functionality does btrfs not support ?
	How do you better keep track of enemy abilities and tactics during combat ?
	Can gamma radiation be used to generate electricity ?
	Prepaying a loan : Shouldn't the interest be recalculated like a shorter loan? 
	Weird colors in Mathematica 10.2
	What is the purpose behind having public holidays in modern times ?
	Uno - measure the voltage, NOT connecting GND
	question feed
	about us tour help blog chat data legal privacy policy work here advertising info developer jobs directory mobile contact us feedback
	Technology
	Life / Arts
	Culture / Recreation
	Science
	Other
	Stack Overflow
	Server Fault
	Super User
	Web Applications
	Ask Ubuntu
	Webmasters
	Game Development
	TeX - LaTeX
	Software Engineering
	Unix & Linux
	Ask Different(Apple)
	WordPress Development
	Geographic Information Systems
	Electrical Engineering
	Android Enthusiasts
	Information Security
	Database Administrators
	Drupal Answers
	SharePoint
	User Experience
	Mathematica
	Salesforce
	ExpressionEngine® Answers
	Cryptography
	Code Review
	Magento
	Signal Processing
	Raspberry Pi
	Programming Puzzles & Code Golf
	more(7)
	Photography
	Science Fiction & Fantasy
	Graphic Design
	Movies & TV
	Music : Practice & Theory
	Seasoned Advice(cooking)
	Home Improvement
	Personal Finance & Money
	Academia
	more(8)
	English Language & Usage
	Skeptics
	Mi Yodeya(Judaism)
	Travel
	Christianity
	English Language Learners
	Japanese Language
	Arqade(gaming)
	Bicycles
	Role - playing Games
	Anime & Manga
	Motor Vehicle Maintenance & Repair
	more(17)
	MathOverflow
	Mathematics
	Cross Validated(stats)
	Theoretical Computer Science
	Physics
	Chemistry
	Biology
	Computer Science
	Philosophy
	more(3)
	Meta Stack Exchange
	Stack Apps
	Area 51
	Stack Overflow Talent
	site design / logo © 2017 Stack Exchange Inc; user contributions licensed under cc by - sa 3.0 with attribution required
	rev 2017.5.11.25889 */