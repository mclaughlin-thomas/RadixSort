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
#include <cmath>

// MAKE RANGE DEPEND ON MAX DIGIT AS WELL 
// Maybe make array dynamic as well
// CHANGE BELOW FOR NUMBER OF PLACES
const int MAX_DIGITS = 4;
// CHANGE ABOVE FOR NUMBER OF PLACES
const int MAX_PLACE = pow(10, (MAX_DIGITS - 1));;
const int TEST_RANGE = 31;

const int TEST_ARRAY_SIZE = 4;

// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void CountingSort(int randomNumbers[], int B[], int digit);

// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void RadixSort(int randomNumbers[], int d);


int main(void) {

    int t_numbers[] = { 15, 22, 30, 5 };;

    RadixSort(t_numbers, 1);
    
    std::cout << "SORTED ARRAY" << std::endl;
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout <<  t_numbers[i] << " ";
    }

    return 0;
}


void CountingSort(int randomNumbers[], int B[], int digitPlace)
{
    int C[TEST_RANGE] = { 0 }; // RANGE acts as K: if goes up to 7 max, the range is 8(0-7)
    int digit;

    //count occurrences
    for (int j = 0; j < TEST_ARRAY_SIZE; j++) {
        digit = (randomNumbers[j] / digitPlace) % TEST_RANGE; // Get the digit at the current place value
        C[digit] = C[digit] + 1;
        //C[randomNumbers[j]] = C[randomNumbers[j]] + 1; //OLD VERSION
        // C[i] now contains the number of elements equal to i.
    }

    //sum up
    for (int i = 1; i < TEST_RANGE; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = TEST_ARRAY_SIZE - 1; j >= 0; j--) {
        digit = (randomNumbers[j] / digitPlace) % TEST_RANGE; // Get the digit at the current place value
        B[C[digit] - 1] = randomNumbers[j];
        C[digit] = C[digit] - 1;
        //B[C[randomNumbers[j]] - 1] = randomNumbers[j]; // using the -1 because i'm starting from 0
        //C[randomNumbers[j]] = C[randomNumbers[j]] - 1;
    }

}

void RadixSort(int randomNumbers[], int d)
{
    int B[TEST_ARRAY_SIZE];   // Array to temporarily hold the data.

    for (int digitPlace = 1; digitPlace <= MAX_PLACE; digitPlace *= 10)
    {
        CountingSort(randomNumbers, B, digitPlace);

        //grabbed from CS 312: Main Project, Stage 3 HW.
        // Now copy B to A. Note that this wastes some time, O(n) time, where n is the length of the array.
        // Note that the actual time wasted is proportional to n * d, but d is the (small) number of digits, so that the time is still O(n).
        for (int k = 0; k < TEST_ARRAY_SIZE; k++)
            randomNumbers[k] = B[k];
    }
}
