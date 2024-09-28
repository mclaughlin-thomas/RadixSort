// Thomas McLaughlin
// Homework 4
// CS-312: Introduction to Algorithms

/*
Summary:  x


Programming Assignment:  Follow our textbook's design of a RADIX-SORT that uses COUNTING-SORT internally.
Use it to sort an array of 4-digit decimal numbers. The array should contain 100 4-digit numbers in
apparent random order at the start. The output should show on the screen the sorted data, perhaps with 10
numbers per line. Follow the pseudocode in our textbook closely. Be careful with lines 12 and 13 especially.
Don't forget the documentation: A summary of what the program does overall at the top of the file containing
main, and documentation for each function other than main, where this documentation is either in the
precondition/postcondition style or given/task/return style.
*/


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>


// CHANGE TO DESIRE BELOW ---
constexpr int MAX_DIGITS = 4;   // Number of places in the form: xxxx.
constexpr int ARRAY_SIZE = 100; // Size of the array.
constexpr int RANGE = 9999;     // 9999 to adhere to 4 place digits, 99999 to adhere to 5 place digits, and so on.
// CHANGE TO DESIRE ABOVE ---
const int MAX_PLACE = static_cast<int>(pow(10, (MAX_DIGITS - 1)));  // Smallest power of 10 that has the number of digits specified by MAX_DIGITS.


// Given:  Numbers      - The array wished to be sorted.
//         B            - A temporary array to store the sorted numbers based upon the current digit place.
//         digitPlace   - The place we wish to evaluate: unit place, tens place, hundreds place, etc.
// 
// Task:   To sort the Numbers array into ascending order based on the digit indicated by the parameter digitPlace.
// 
// Return: B            - Containing the data from numbers which is sorted into ascending order by the digitPlace.
void CountingSort(int Numbers[], int B[], const int digitPlace);


// Given:  Numbers      - An array of unsorted integers.
//         maxPlace     - Integer which is the smallest power of 10 that has the number of digits specified by MAX_DIGITS.
// 
// Task:   To sort the integers in the Numbers array into ascending order using Radix Sort (with CountingSort as its stable sort).
// 
// Return: Numbers      - An array of integers, now in sorted, ascending order.
void RadixSort(int Numbers[], const int maxPlace);


// Given:  Numbers      - An array to be populated with random integers.
//         size         - The size of the array.
//         maxDigits    - The maximum number of desired digits for each integer in numbers array.
// 
// Task:   Populate the Numbers array with random integers, where each integer has a maximum of
//         maxDigits places. The random integers are generated in the range from 10^(n-1) to the largest
//         number that can be represented without exceeding the maximum number of places: maxDigits.
// 
// Return: Numbers      - An array of integers populated with random integers with the desired number of places.
void populateArray(int Numbers[], const int size ,const int maxDigits);



int main(void) {

    std::srand((unsigned)time(0)); // Seeding with time to guarantee different set of numbers each run.

    int Numbers[ARRAY_SIZE];
    populateArray(Numbers, ARRAY_SIZE, MAX_DIGITS); // Populate the Numbers array with random numbers in specified range.

    RadixSort(Numbers, MAX_PLACE); // Sort the Numbers array in ascending order.

    // Output the newly sorted array.
    std::cout << "SORTED ARRAY" << std::endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::cout << Numbers[i] << " ";

        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }

    return 0;
}



void CountingSort(int Numbers[], int B[], const int digitPlace) {

    // Counting Sort has a worst case time of theta ( k + n )
    // Counting Sort has an average case time of theta ( k + n )
    // Where k is the # of values.

    //      COUNTING-SORT(A, n, k)
    // 1         let B[1:n] and C[0:k] be new arrays   | I instead initialized all of C's elements to 0 w/o a loop, and passed in array B.
    // 2         for i = 0 to k
    // 3             C[i] = 0                          | Concatenated line with: int C[RANGE] = { 0 };
    // 4         for j = 1 to n
    // 5             C[A[j]] = C[A[j]] + 1
    // 6         // C[i] now contains the number of elements equal to i.
    // 7         for i = 1 to k
    // 8             C[i] = C[i] + C[i - 1]
    // 9         // C[i] now contains the number of elements less than or equal to i.
    // 10        // Copy A to B, starting from the end of A.
    // 11        for j = n down to 1
    // 12            B[C[A[j]]] = A[j]
    // 13            C[A[j]] = C[A[j]] - 1
    // 14        return B                              | B[] was passed in by reference as a parameter, we 'return' B this way.

    int C[RANGE] = { 0 }; // RANGE acts as K: if max number goes up to 7, the range is 8 (0-7).
    int digit;

    // Count the occurrences.
    for (int j = 0; j < ARRAY_SIZE; j++) {
        digit = (Numbers[j] / digitPlace) % RANGE; // Get the digit at the current place value.
        C[digit] = C[digit] + 1;
        // C[i] now contains the number of elements equal to i.
    }

    // Sum up elements across array.
    for (int i = 1; i < RANGE; i++) {
        C[i] = C[i] + C[i - 1];
    }

    // Copy numbers to array B, starting from the end of the Numbers array.
    for (int j = ARRAY_SIZE - 1; j >= 0; j--) {
        digit = (Numbers[j] / digitPlace) % RANGE; // Get the digit at the current place value.
        B[C[digit] - 1] = Numbers[j]; // Put the element in its proper location in B based on the digit.
        C[digit] = C[digit] - 1; // Decrement the count so we can handle duplicates.
    }

}


void RadixSort(int Numbers[], const int maxPlace) {

    // Radix Sort has a worst case time of theta ( d (n + k) )
    // Radix Sort has an average case time of theta ( d (n + k) )
    // Where k is the # of values, d is the # of digits, and n is the length of the array.

    //      RADIX-SORT(A, n, d)
    // 1         for i = 1 to d
    // 2             use a stable sort to sort array A[1:n] on digit i
    
    int B[ARRAY_SIZE];   // Array to temporarily hold the data.

    // Iterate over each digit place
    for (int digitPlace = 1; digitPlace <= maxPlace; digitPlace *= 10) {

        CountingSort(Numbers, B, digitPlace); // CountingSort will sort based on the provided digit place.

        // Now copying B to Numbers array. Note that this wastes some time, O(n) time, where n is the length of the array.
        for (int k = 0; k < ARRAY_SIZE; k++) {
            Numbers[k] = B[k];
        }

    }

}


void populateArray(int Numbers[], const int size, const int maxDigits) {

    const int maxPlace = static_cast<int>(pow(10, maxDigits)) - 1; // With current MAX_DIGITS, the maximum random value is 9999.
    const int minPlace = static_cast<int>(pow(10, maxDigits-1)); // With current MAX_DIGITS, the maximum random value is 1000.

    // Generate random maxDigits digit numbers
    for (int i = 0; i < size; i++) {
        Numbers[i] = std::rand() % ( maxPlace - minPlace + 1 ) + minPlace; // Provides numbers from minPlace to 1 below next 10^n: (10^(n) -1 ).Thus resulting in numbers that have no more than our desired places of digits.
    }

}
