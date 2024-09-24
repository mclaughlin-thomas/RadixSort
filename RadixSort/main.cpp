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
const int RANGE = 100;
const int SHIFT_AMMOUNT = 1000;

const int TEST_ARRAY_SIZE = 4;
const int TEST_RANGE = 6;


int main(void) {

    std::srand((unsigned)time(0));

    int t_numbers[] = { 5, 2, 0, 3};

    CountingSort(t_numbers);
    

    return 0;
}



void CountingSort(int randomNumbers[], int B[])
{
    int C[TEST_RANGE]; // RANGE acts as K: if goes up to 7 max, the range is 8(0-7)

    for (int i = 0; i < TEST_RANGE; i++) {
        C[i] = 0;
    }

    for (int j = 0; j < TEST_ARRAY_SIZE; j++) {
        C[randomNumbers[j]] = C[randomNumbers[j]] + 1;
        // C[i] now contains the number of elements equal to i.

    }

    /*for (int i = 0; i < TEST_RANGE; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << "TESTING COUNT OF C \n\n";*/

    for (int i = 1; i < TEST_RANGE; i++) {
        C[i] = C[i] + C[i - 1];
    }

    /*for (int i = 0; i < TEST_RANGE; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << "OUTPUT OF C \n\n";*/



    for (int j = TEST_ARRAY_SIZE - 1; j >= 0; j--) {
        B[C[randomNumbers[j]] - 1] = randomNumbers[j]; // using the -1 because i'm starting from 0
        C[randomNumbers[j]] = C[randomNumbers[j]] - 1;
    }

    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout << B[i] << " ";
    }
    std::cout << "SORTED OUTPUT OF ARR \n\n"; //should be 0 2 3 5
    //return that b
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


void RadixSort(int randomNumbers[], int d)
{
    int B[TEST_ARRAY_SIZE];   // Array to temporarily hold the data.

    for (int digit = 1; digit <= d; digit++)
    {
        CountingSort(randomNumbers, B, digit);
        // Now copy B to A. Note that this wastes some time, O(n) time, where n is the length of the array.
        // Note that the actual time wasted is proportional to n * d, but d is the (small) number of digits, so that the time is still O(n).
        for (int k = 0; k < MaxPlusOne; k++)
            A[k] = B[k];
    }
}

//      RADIX-SORT(A, n, d)
//1         for i = 1 to d
//2             use a stable sort to sort array A[1:n] on digit i
