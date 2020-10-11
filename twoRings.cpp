/**
// Two Rings Project

// Processor 0 and 1 are the starting processes. 
// Process 0 will send a message to the NEXT EVEN process
// Process 1 will send a message to the PREVIOUS ODD process.
// Once the final even / odd process is reached, the program will send the 
// message back to its respective starting process.

Author: Jordan Wendel
*/

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah


#include <iostream>
#include <stdio.h>
#include <string.h>
#include "mpi.h"
using namespace std;

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

    //Starting point for even processors
    if (my_rank == 0) 
	{
		cout << "Processor " << my_rank <<" tells processor " << my_rank + 2 << " that frodo is lame. " << endl;
		sprintf(message + strlen(message),"%d",my_rank);
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, my_rank+2, tag, MPI_COMM_WORLD);
		MPI_Recv(message, 100, MPI_CHAR, p, tag, MPI_COMM_WORLD, &status);
	}
	
	//Starting point for odd processors
	else if (my_rank == 1)
	{
		//When there is an even number of total processors
		if (p % 2 == 0)
		{
			cout << "Processor " << my_rank << " tells processor "<< p - 1 << " that frodo is just not cool, man. " << endl;
			sprintf(message+strlen(message),"%d",my_rank);
			MPI_Send(message, strlen(message) + 1, MPI_CHAR, p-1, tag, MPI_COMM_WORLD);
			MPI_Recv(message, 100, MPI_CHAR, my_rank+2, tag, MPI_COMM_WORLD, &status);
		}
		//When there is an odd number of total processors
		else
		{
		    cout << "Processor " << my_rank << " tells processor "<< p - 2 << " that frodo is just not cool, man. " << endl;
		    sprintf(message+strlen(message),"%d",my_rank);
		    MPI_Send(message, strlen(message) + 1, MPI_CHAR, p - 2, tag, MPI_COMM_WORLD);
		    MPI_Recv(message, 100, MPI_CHAR, my_rank + 2, tag, MPI_COMM_WORLD, &status);
		}
	}
	//Remaning processors when there is an even total number of processors
	else if (p % 2 == 0)
	{
		//The rest of the even processors
		if (my_rank % 2 == 0)
		{
		    MPI_Recv(message, 100, MPI_CHAR, my_rank - 2, tag, MPI_COMM_WORLD, &status);
		    cout << "Processor " << my_rank << " tells processor " << (my_rank+2) % p << " that frodo is lame. " << endl;
		    sprintf(message + strlen(message), "%d", my_rank);
		    MPI_Send(message, strlen(message) + 1, MPI_CHAR, (my_rank + 2) % p, tag, MPI_COMM_WORLD);
		}
		//The rest of the odd processors
		else
		{
		    MPI_Recv(message, 100, MPI_CHAR, (my_rank+2)%p, tag, MPI_COMM_WORLD, &status);
		    cout<<"Processor "<<my_rank<<" tells processor "<< my_rank - 2 << " that frodo is just not cool, man. " << endl;
		    sprintf(message+strlen(message),"%d",my_rank);
		    MPI_Send(message, strlen(message) + 1, MPI_CHAR, my_rank-2, tag, MPI_COMM_WORLD);
		}
		
	}
	//Remaining processors when there is an odd total number of processors
	else 
	{
		//The rest of the even processors
		if (my_rank% 2==0)
		{
			MPI_Recv(message, 100, MPI_CHAR, my_rank-2, tag, MPI_COMM_WORLD, &status);
			cout <<"Processor " << my_rank <<" tells processor "<< (my_rank + 2) % (p + 1) << " that frodo is lame." << endl;
			sprintf(message+strlen(message),"%d",my_rank);
			MPI_Send(message, strlen(message)+1, MPI_CHAR,(my_rank+2)%(p+1),tag, MPI_COMM_WORLD);
		}
		//The rest of the odd processors
		else
		{
			MPI_Recv(message, 100, MPI_CHAR, (my_rank+2)%(p-1), tag, MPI_COMM_WORLD, &status);
			cout<<"Processor " << my_rank << " tells processor " << my_rank - 2 << " that frodo is just not cool, man. " << endl;
			sprintf(message+strlen(message),"%d",my_rank);
			MPI_Send(message, strlen(message)+1, MPI_CHAR,my_rank-2,tag, MPI_COMM_WORLD);
		}
	}

    MPI_Finalize();


    return 0;

}
