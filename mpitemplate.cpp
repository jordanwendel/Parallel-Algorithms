#include <iostream>
#include <stdio.h>
#include <string.h>
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
    sprintf(message, "Yo, baby, a triple! %d %d", my_rank, p);

	MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD); // MPI_COMM_WORLD = world community, 1 = who you are sending to, MPI_CHAR = type of data 

	if(my_rank == 0)
	{
		for(int x = 0; x < p; x++)
		{
			MPI_Recv(message, 100, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status); // 100 = max length of message, MPI_CHAR = type willing to recieve, x = who sent it to you, status = receipt of message
			cout << message << endl;
		}
	}
	

	cout << message << endl;



	// Shut down MPI
	MPI_Finalize();

	return 0;
}