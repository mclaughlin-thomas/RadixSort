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
#include <cstdlib>      // For rand()
#include <cmath>        // For pow()
#include <ctime>        // For time()


// CHANGE TO DESIRE ---
constexpr int MAX_DIGITS = 4;          // Numbers in the form: xxxx
constexpr int TEST_ARRAY_SIZE = 100;   // Size of the array
constexpr int TEST_RANGE = 9999;       // 9999 to adhere to 4 digit, 99999 to adhere to 5 digit, and so on.
// CHANGE TO DESIRE ---
const int MAX_PLACE = static_cast<int>(pow(10, (MAX_DIGITS - 1)));  // Smallest power of 10 that has the number of digits specified by MAX_DIGITS


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
void RadixSort(int numbers[], const int maxPlace);

// Given:  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Task:   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
// Return: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.
void populateArray(int numbers[], const int size ,const int maxDigits);


int main(void) {
    
    std::srand((unsigned)time(0)); // Seeding with time to guarantee different set of numbers each run

    int numbers[TEST_ARRAY_SIZE];
    populateArray(numbers, TEST_ARRAY_SIZE, MAX_DIGITS); // Populate the numbers array with random numbers in specified range

    RadixSort(numbers, MAX_PLACE); // Sort the numbers array in ascending order
    
    // Output the newly sorted array
    std::cout << "SORTED ARRAY" << std::endl;
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout <<  numbers[i] << " ";
    }

    return 0;
}


void CountingSort(int numbers[], int B[], const int digitPlace) {

    int C[TEST_RANGE] = { 0 }; // RANGE acts as K: if goes up to 7 max, the range is 8 (0-7)
    int digit;

    //count occurrences
    for (int j = 0; j < TEST_ARRAY_SIZE; j++) {
        digit = (numbers[j] / digitPlace) % TEST_RANGE; // Get the digit at the current place value
        C[digit] = C[digit] + 1;
        //C[randomNumbers[j]] = C[randomNumbers[j]] + 1; //OLD VERSION
        // C[i] now contains the number of elements equal to i.
    }

    //sum up
    for (int i = 1; i < TEST_RANGE; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = TEST_ARRAY_SIZE - 1; j >= 0; j--) {
        digit = (numbers[j] / digitPlace) % TEST_RANGE; // Get the digit at the current place value
        B[C[digit] - 1] = numbers[j];
        C[digit] = C[digit] - 1;
        //B[C[randomNumbers[j]] - 1] = randomNumbers[j]; // using the -1 because i'm starting from 0
        //C[randomNumbers[j]] = C[randomNumbers[j]] - 1;
    }

}

void RadixSort(int numbers[], const int maxPlace) {
    
    int B[TEST_ARRAY_SIZE];   // Array to temporarily hold the data.

    // Iterate over each digit place
    for (int digitPlace = 1; digitPlace <= maxPlace; digitPlace *= 10) {
        
        CountingSort(numbers, B, digitPlace); // CountingSort will sort based on the provided digit place

        // Now copying B to randomNumbers. Note that this wastes some time, O(n) time, where n is the length of the array
        for (int k = 0; k < TEST_ARRAY_SIZE; k++) {
            numbers[k] = B[k];
        }
          
    }

}

void populateArray(int randomNumbers[], const int size, const int maxDigits) {
    
    const int maxPlace = static_cast<int>(pow(10, maxDigits));

    // Generate random maxDigits digit numbers
    for (int i = 0; i < size; ++i) {
        randomNumbers[i] = std::rand() % maxPlace; // Provides numbers from 0 to 1 below next 10^n (10^(n) -1 ), thus resulting in numbers that have no more than our desired places of digits
    }

}