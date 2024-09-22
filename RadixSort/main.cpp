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