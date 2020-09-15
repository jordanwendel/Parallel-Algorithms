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

    char * baton = message;
    sprintf(baton, "Sent list: ");
    sprintf(baton + strlen(baton), "&d ", my_rank);
    
	if (my_rank == 0) {
		cout << "SUCK IT, FOR I AM THE CHOSEN ZERO!" << endl;
		cout<< "Run, process " << my_rank << " RUN! " << endl;
		MPI_Send(baton, strlen(baton) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
		MPI_Recv(baton, 100, MPI_CHAR, 4, tag, MPI_COMM_WORLD, &status);
		cout << "Declare a provisional victory!" << endl;
		cout << baton << endl;
	}
	else if (my_rank == 1) {
		MPI_Recv(baton, 100, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		sprintf(baton + strlen(baton), "&d ", my_rank);
		cout<< "Run, process " << my_rank << " RUN! " << endl;
		MPI_Send(baton, strlen(baton) + 1, MPI_CHAR, 2, tag, MPI_COMM_WORLD);
		cout << baton << endl;
	}
	else if (my_rank == 2) {
		MPI_Recv(baton, 100, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
		sprintf(baton + strlen(baton), "&d ", my_rank);
		cout<< "Run, process " << my_rank << " RUN! " << endl;
		MPI_Send(baton, strlen(baton) + 1, MPI_CHAR, 3, tag, MPI_COMM_WORLD);
		cout << baton << endl;
	}
	else if (my_rank == 3) {
		MPI_Recv(baton, 100, MPI_CHAR, 2, tag, MPI_COMM_WORLD, &status);
		sprintf(baton + strlen(baton), "&d ", my_rank);
		cout<< "Run, process " << my_rank << " RUN! " << endl;
		MPI_Send(baton, strlen(baton) + 1, MPI_CHAR, 4, tag, MPI_COMM_WORLD);
		cout << baton << endl;
	}
	else if (my_rank == 4) {
		MPI_Recv(baton, 100, MPI_CHAR, 3, tag, MPI_COMM_WORLD, &status);
		sprintf(baton + strlen(baton), "&d ", my_rank);
		cout<< "Run, process " << my_rank << " RUN! " << endl;
		MPI_Send(baton, strlen(baton) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
		cout << baton << endl;
	}


 	// Shut down MPI
	MPI_Finalize();

	return 0;
} 