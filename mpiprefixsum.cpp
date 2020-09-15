#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
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
	int n = 9;
	int * a = new int[n];
	long * psum = new long[n];
	
	if (my_rank == 0) {
		for (int x = 0; x < n; x++) {
			a[x] = rand() % 8;
			cout << setw(3) << a[x] << " ";
		}
		cout << endl;
	}
	
	// DIVIDE THE PROBLEM UP
	int * locala = new int[n/p];
	long * localpsum = new long[n/p];
	
	MPI_Scatter(&a[0], n/p, MPI_INT, locala, n/p, MPI_INT, 0, MPI_COMM_WORLD);
	
	// DO THE LOCAL WORK
	localpsum[0] = locala[0];
	for (int x = 1; x < n/p; x++)
		localpsum[x] = locala[x] + localpsum[x-1];
	// Declare a provisional victory on this??!?~
    // Fail.

    // Send last partial prefix sum answer to all later processors
   for (int x = my_rank + 1; x < p; x++)
        MPI_Send(&localpsum[n/p-1], 1, MPI_LONG, x, tag, MPI_COMM_WORLD);


    // Recieve all the answers from processors before me
    long local_additive = 0;
    long temp;
    for (int x = 0; x < my_rank; x++) {
        MPI_Recv(&temp, 1, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
        local_additive += temp;
    }


    // Add the local_additive to all entries of our localpsum
    for (int x = 0; x < n/p; x++)
        localpsum[x] += local_additive;


	
	// COLLECT ALL ANSWERS BACK TOGETHER IN A HAPPY ENDING
	MPI_Gather(localpsum, n/p, MPI_LONG, psum, n/p, MPI_LONG, 0, MPI_COMM_WORLD);
	
	if (my_rank == 0) {
		for (int x = 0; x < n; x++)
			cout << setw(3) << psum[x] << " ";
		cout << endl;
	}
	
	delete [] a;
	delete [] psum;
	delete [] locala;
	delete [] localpsum;
	
 	// Shut down MPI
	MPI_Finalize();

	return 0;
}