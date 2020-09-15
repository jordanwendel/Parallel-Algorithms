#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;


int rank (int * a, int first, int last, int valToFind)  
{ // Binary Search to find the rank
    int middle = 0;
    int number=0;
    int n = 5;

    while (first <= last) {
        // First compare valToFind with middle element
        middle = n / 2;

        // If target value is greater than middle, continue search in upper half of array
        if (a[middle] < valToFind) {
            first = middle + 1;
        }
        // If target value is less than middle, continue search in lower half of array
        else if (a[middle] > valToFind) {
            last = middle - 1;
        }
        // If target value matches middle, return its position
        else {
            if (a[middle] == valToFind)
                middle++;
            return middle;
        }
        
    }
}

int main (int argc, char * argv [])
{
    int ranks = 0;
    int * a = new int[5];
    for (int i = 0; i < 5; i++)
        a[i]=0;
    a[0]=9;
    a[1]=12;
    a[2]=12;
    a[3]=12;
    a[4]=12;

    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl;
    for (int i =0; i<5; i++) {
        
        ranks = rank(a, 0, 4, 12);
    }
    cout << ranks << endl;
    


}