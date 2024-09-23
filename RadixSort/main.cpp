// Thomas McLaughlin
// Homework 4
// CS-312: Introduction to Algorithms

/*
Programming Assignment:  Follow our textbook's design of a RADIX-SORT that uses COUNTING-SORT internally.
Use it to sort an array of 4-digit decimal numbers. The array should contain 100 4-digit numbers in
apparent random order at the start. The output should show on the screen the sorted data, perhaps with 10
numbers per line. Follow the pseudocode in our textbook closely. Be careful with lines 12 and 13 especially.
Don't forget the documentation: A summary of what the program does overall at the top of the file containing
main, and documentation for each function other than main, where this documentation is either in the
precondition/postcondition style or given/task/return style.
*/

#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

const int ARRAY_SIZE = 100;

void populateArray(int randomNumbers[], const int count);


int main(void) {

    std::srand((unsigned)time(0));

    int numbers[ARRAY_SIZE];
    populateArray(numbers, ARRAY_SIZE);

    return 0;
}

void populateArray(int randomNumbers[], const int count) {
    const int min = 1000;
    const int max = 9999;

    // Generate random 4 digit numbers
    for (int i = 0; i < count; ++i) {
        randomNumbers[i] = min + std::rand() % ((max - min) + 1);
    }
}


//      COUNTING-SORT(A, n, k)
//1         let B[1:n] and C[0:k] be new arrays
//2         for i = 0 to k
//3             C[i] = 0
//4         for j = 1 to n
//5             C[A[j]] = C[A[j]] + 1
//6         // C[i] now contains the number of elements equal to i.
//7         for i = 1 to k
//8             C[i] = C[i] + C[i - 1]
//9         // C[i] now contains the number of elements less than or equal to i.
//10        // Copy A to B, starting from the end of A.
//11        for j = n down to 1
//12            B[C[A[j]]] = A[j]
//13            C[A[j]] = C[A[j]] - 1     // to handle duplicate values
//14 return B

//      RADIX-SORT(A, n, d)
//1         for i = 1 to d
//2             use a stable sort to sort array A[1:n] on digit i