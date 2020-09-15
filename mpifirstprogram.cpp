#include <iostream>
#include <stdio.h>
#include <string>
#include "mpi.h"  // Message Passing Interface (MPI)
using namespace std;


//  The following line is to compile your program
// 		mpicxx <yourProgram>.cpp -o a.out 

// The following line is to run your compiled program   
// 		mpirun -np 32 a.out


int main(int argc, char * argv[])
{
	int myRank;  		// My CPU number for this program
	int numCPUs;		// Number of CPUs that we have
	int sourceRank;		// Rank of the sender
	int destRank;		// Rank of destination
	int msgNum = 0;		// Message Number
	string msg;		// The Message itself
	MPI_Status status;	// Return status for receive

	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	
	// Find out the number of processess!
	MPI_Comm_size(MPI_COMM_WORLD, &numCPUs);
	
	// The REAL Program
	cout << myRank << " is alive " << endl;
	if(myRank %2 == 0)
	{
		cout << myRank << " is on the left!"  << endl;
	}
	else
	{
		cout << myRank << " is on the right!"  << endl;
	}
	
	
	// Shut down MPI
	MPI_Finalize();
	
	return 0;
}