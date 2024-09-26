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
#include <cmath>
#include <ctime>    // For time()


// CHANGE TO DESIRE ---
constexpr  int MAX_DIGITS = 4; // digits in the form: xxxx
constexpr  int TEST_ARRAY_SIZE = 100;
constexpr  int TEST_RANGE = 9999; // 9999 to adhere to 4 digit, 99999 to adhere to 5 digit, and so on.
// CHANGE TO DESIRE ---
const int MAX_PLACE = pow(10, (MAX_DIGITS - 1));


// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void CountingSort(int randomNumbers[], int B[], const int digitPlace);

// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void RadixSort(int randomNumbers[]);

// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void populateArray(int randomNumbers[], const int size ,const int maxDigits);



int main(void) {
    
    std::srand((unsigned)time(0));

    int  numbers[TEST_ARRAY_SIZE];
    populateArray(numbers, TEST_ARRAY_SIZE, MAX_DIGITS); // Populate the numbers array with random numbers in specified range

    RadixSort(numbers); // Sort the numbers array in ascending order
    
    // Output the newly sorted array
    std::cout << "SORTED ARRAY" << std::endl;
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout <<  numbers[i] << " ";
    }

    return 0;
}


void CountingSort(int randomNumbers[], int B[], const int digitPlace)
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

void RadixSort(int randomNumbers[]){
    
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

void populateArray(int randomNumbers[], const int size, const int maxDigits) {
    
    int maxPlace = pow(10, maxDigits);

    // Generate random 4 digit numbers
    for (int i = 0; i < size; ++i) {
        randomNumbers[i] = std::rand() % maxPlace; // 0 to 1 below next 10^n (10^(n) -1 ), thus satisfying # of digits
    }
}