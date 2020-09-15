#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include "mpi.h"  // Message Passing Interface (MPI)
using namespace std;

// Do this ONCE when you start up Thomas.Butler.edu to set to a 64 bit processor
//		module load openmpi -x86_64

//  The following line is to compile your program
// 		mpicxx <yourProgram>.cpp -o a.out 

// The following line is to run your compiled program   
// 		mpirun -np 32 a.out


const int MessageSize = 100;

int main(int argc, char * argv[])
{
	int myRank;  		// My CPU number for this program
	int numCPUs;		// Number of CPUs that we have
	int sourceRank;		// Rank of the sender
	int destRank;		// Rank of destination
	int msgNum = 0;		// Message Number
	char msg[MessageSize];		// The Message itself    <<< ----- why an array of characters??????
	
	MPI_Status status;	// Return status for receive

	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	
	// Find out the number of processess!
	MPI_Comm_size(MPI_COMM_WORLD, &numCPUs);
	
	// The REAL Program
	
	// Want to do the following
	// int topNumber = 300000;
	// double sum = 0;
	// for (int loopVariable = 0; loopVariable < topNumber; loopVariable++)
	// {
		// sum = sum + loopVariable;
	// }
	// cout << "The sum is = " << sum << endl;
	
	// -------------------- Know the problem --------------------
	int topNumber = 300000;
	double finalSum = 0;
	
	// -------------------- Break the problem into smaller pieces --------------------
	int localStart = myRank * (topNumber/numCPUs) + 1;         //  This is the range to START at
	int localStop =  (myRank + 1) * (topNumber/numCPUs);   //  This is the range to END at
	
	//Handle any potential remainders
	if( (topNumber - localStop) < (localStop - localStart + 1))
	{
		localStop = topNumber;
	}
		
	// -------------------  Do local work	 --------------------
	double localSum = 0;
	// For the local work sum up your parts
	for(int loopVariable = localStart; loopVariable <= localStop;  loopVariable++)
	{
		localSum = localSum + loopVariable;
	}
	
	
	cout << myRank << " :: local sum = " << fixed << setprecision(2) << localSum << "  Start = " << localStart << " End = " << localStop << endl;
	cout << endl;
	
	//  -------------------- Collect :: Sum up the parts  --------------------
	if ( myRank != 0)
	{
		// I am not the summing process so send my results to the summing process 0
		MPI_Send(&localSum, 1, MPI_DOUBLE, 0, msgNum, MPI_COMM_WORLD);
	}
	else
	{
		// I am process 0
		// Sum up my local piece as I did work too
		finalSum =  localSum;
		double tempSum;
		for(int loopVariable2 = 1; loopVariable2 < numCPUs; loopVariable2++)
		{
			// Search for the results of each of the pieces
			MPI_Recv(&tempSum, 1, MPI_DOUBLE, loopVariable2, msgNum, MPI_COMM_WORLD, &status);	
			finalSum = finalSum + tempSum;
		}		
	}
	
	//  -------------------- Print out the final results  --------------------
	if(myRank == 0)
	{
		// Only print out the final result if am Process 0
		cout << "The final sum is = " << fixed << setprecision(2) << finalSum << endl;
	}
	
	// Shut down MPI
	MPI_Finalize();
	
	return 0;
}