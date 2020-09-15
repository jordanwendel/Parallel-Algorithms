/**
// In Your Eye Project
// Takes in a text file and counts the amount of each letter within that file
// Prints out the number of each at the end

Author: Jordan Wendel
*/


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
#include <fstream>
#include <iomanip>
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
	
	// KNOW THE PROBLEM
    // Create array for letters in text file
    int i=1000;
    char * characters = new char[i];
    int * integers = new int[i];

    ifstream file;
	file.open("letters.txt");

    // Collects all letters onto processor 0 into array a
    int n = 0;
	int numLetters=0;
	while (!file.eof()) {
        // Imports each character into an array
		file >> characters[n];
        n++;
	}
    cout << endl;

	

    

    // DIVIDE PROBLEM UP
        int * localinteger[26] = {0};
		char * localcharacters = new char[n/p];
		
        // Scatter
		MPI_Scatter(&characters[0], n/p, MPI_CHAR, localcharacters, n/p, MPI_CHAR, 0, MPI_COMM_WORLD);
		
        // Counts amount of each letter and stores the answer into array acording to respective ascii value
		for (int x = 0; x < n/p; x++)
		{
			localinteger[(int)localcharacters[x]-97]++;
		}
		
        // Reduces answers back to integer array
		for (int x = 0; x < 26; x++)
		{
			MPI_Reduce(&localinteger[x], &integers[x], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		}
	
		delete [] localcharacters;
		
        // Prints out answers that are reduced to processor 0
		if (my_rank == 0)
		{
			for (int x = n - (n % p); x < n; x++)
			{
				integers[(int)characters[x]-97]++;
			}
			
			int local_additive=0;
			
			for (int x = 0; x < 26; x++)
			{
				cout << "There are " << integers[x] << " counts of " << (char)( x+ 97 ) << endl;
				local_additive += integers[x];
			}
				
		}
	
		delete [] integers;
		delete [] characters;

	// Shut down MPI
	MPI_Finalize();

	return 0;
}
