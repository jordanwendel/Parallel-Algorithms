/**
// Whack An Orc Project
// Calculates min, max, and average of a list of random numbers
// by scattering and reducing

Author: Jordan Wendel
*/

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah



#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <iomanip>
using namespace std;

//Max function
// Compares two long int numbers and returns the max of the two
long int maximum (long int num1, long int num2) {
	int max = 0;

	if (num1 > num2)
		max = num1;
	else
		max = num2;

	return max;
}

//Min function
// Compares two long int numbers and returns the min of the two
long int minimum (long int num1, long int num2) {
	int min = 0;

	if (num1 < num2)
		min = num1;
	else
		min = num2;
	
	return min;
}


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

	srand(71911);
	int n = 300000;
	int * a = new int[n];
	int * b = new int[n];
	int max = 0;
	int min = 0;

	// Fill array with random numbers on process 0
	if(my_rank==0)
		for (int x = 0; x < n ; x++) {
			a[x] = rand() % 8;
			b[x] = rand() % 8;
		}

	// DIVIDE PROBLEM INTO PIECES
	int localn = n/p;
	int * locala = new int[localn];
	int * localb = new int[localn];
	int sum = 0;

	// Scatter
	MPI_Scatter(&a[0], localn, MPI_INT, locala, localn, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&b[0], localn, MPI_INT, localb, localn, MPI_INT, 0, MPI_COMM_WORLD);


	// DO LOCAL WORK
	
	// Local max
	int localMax = 0;
	int localMax2 = 0;
	for (int x = 0; x < localn; x++) {
		localMax = maximum(locala[x], localb[x]);
	}

	// Takes each local max and uses the MPI_MAX function to determine the global max
	MPI_Allreduce(&localMax, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
	


	// Local min
	int localMin = 0;
	for (int x = 0; x < localn; x++)
		localMin = minimum(locala[x], localb[x]);

	// Takes each local min and uses the MPI_MIN function to determine the global min
	MPI_Allreduce(&localMin, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

	long int localSumA = 0;
	long int localSumB = 0;

	// Calculates the local sum for each local set
	for (int x = 0; x < localn; x++) {
		localSumA += locala[x];
		localSumB += localb[x];
	}

	// Reduces all local sums of set A to global sum of set A
	long int globalSumA = 0;
	MPI_Allreduce(&localSumA, &globalSumA, 1, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);

	// Reduces all local sums of set B to global sum of set B
	long int globalSumB = 0;
	MPI_Allreduce(&localSumB, &globalSumB, 1, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);

	// Creates global sum of both sets
	sum = globalSumA + globalSumB;

	// Caluculates global average using the global sums 
	long int average = 0;
	average = sum / n;

	cout << "Average: " << average << endl;
	cout << "Max: " << max << endl;
	cout << "Min: " << min << endl;

	delete [] a;
	delete[] b;
	delete [] locala;
	delete [] localb;

    // Very large array of integers
    // Find max, min, and average
    // SCATTER the array into pieces to each process
    // (just once at the beginning)
    // Each process computes a partial answer
    // REDUCE back the answer together on process 0



    MPI_Finalize();

    return 0;
}
