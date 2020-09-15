#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h" // message passing interface
using namespace std;

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah

int main (int argc, char * argv[]) {

	int my_rank;			// my CPU number for this process
	int p;					// number of CPUs that we have
	int source;				// rank of the sender
	int dest;				// rank of destination
	int tag = 0;			// message number
	char message[100];		// message itself
	MPI_Status status;		// return status for receive
	
	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// Find out the number of processes!
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// THE REAL PROGRAM IS HERE

	// KNOW THE PROBLEM
	// Hint: It's still you. (memey joke)
	
	//srand(time(0));
	srand(1241);
	int n = 300000;
	int * a = new int[n];
	int * b = new int[n];
	long int dotproduct = 0;	
	
	// Fill in the array with random numbers on process 0
	if (my_rank == 0)
		for (int x = 0; x < n; x++) {
			a[x] = rand() % 8;
			b[x] = rand() % 8;
		}
	
	// DIVIDE THE PROBLEM UP INTO PIECES
	int localn = n/p;
	int * locala = new int[localn];
	int * localb = new int[localn];	
	
	// After executing the lines of code below, locala and localb will have the "right"
	// info in them.
	// In other words, each array will have the block of array a (or b) that corresponds
	// to the local information that they should have for their rank
	MPI_Scatter(&a[0], localn, MPI_INT, locala, localn, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&b[0], localn, MPI_INT, localb, localn, MPI_INT, 0, MPI_COMM_WORLD);

	// DO THE LOCAL WORK
	long int localdot = 0;
	for (int x = 0; x < localn; x++)
		localdot += locala[x] * localb[x];
	
	// COLLECT THE RESULTS BACK TOGETHER
	MPI_Reduce(&localdot, &dotproduct, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	
	delete [] a;
	delete [] b;
	delete [] locala;
	delete [] localb;
 
 	// Shut down MPI
	MPI_Finalize();

	return 0;
}