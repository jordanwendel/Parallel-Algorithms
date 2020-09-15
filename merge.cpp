#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using namespace std;
void move (int * a1, int first1, int last1, int * a2, int first2)
{
    while (first1 <= last1)
        a2[first2++] = a1[first1++];
}

void merge(int *a, int size, int first1, int last1, int first2, int last2)
{
    int temp[size];
    int index, index1, index2;
    int num;

    index = 0;
    index1 = first1;
    index2 = first2;

    num = last1 - first1 + last2 - first2 + 2;

    //Merge two lists together until one list runs out of items

    while ((index1 <= last1) && (index2 <= last2)) {
        if (a[index1] < a[index2])
            temp[index++] = a[index1++];
        else
            temp[index++] = a[index2++];
    }

    //fill in the merged list with the "rest" of the non exhausted list.

    if (index1 > last1)
        move (a, index2, last2, temp, index);
    else
        move (a, index1, last1, temp, index);
        
    // finally move merged array in temp to real array
        move(temp, 0, num-1, a, first1);
}

void mergesort(int *a, int first, int last)
{
    int middle;
    int * b = new int [1000000];
    if (first < last)
    {
        middle = (first + last)/2; //pivot
		
		//recursivelj merge sort
        mergesort(a, first, middle);
        mergesort(a, middle + 1, last);
        merge(a, b, first, middle, last);
    }
}

int main(int argc, char * argv[])
{
    int n;
	cout << "Array size: "; 
	cin >> n;
    int *a = new int [n];
	
	cout << "Unsorted: ";
	
    for (int i = 0; i < n; i++) // assign random numbers to array and print themn
	{	
		a[i] = rand() % 100;
		cout << a[i] << " ";
	}

	cout << endl;


    mergesort(a, 0, n-1);

	cout<<"Sorted: ";

	for (int i = 0; i < n ; i++) // print array values
	{
		cout << a[i] << " ";
	}
    
    
    cout << endl;
	return 0; 
}