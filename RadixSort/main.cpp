// Thomas McLaughlin
// Homework 4
// CS-312: Introduction to Algorithms

/*
Summary:  
          This program follows our textbook's design of RADIX-SORT that uses COUNTING-SORT internally as
          its stable sort. I have RADIX-SORT set to sort through an array of randomized 4 digit numbers.
          Currently the array has 100 4-digit numbers, but the size of the array can be adjusted by
          modifying the ARRAY_SIZE variable to desired size. Also, the program can be modified to evaluate
          numbers less than, or more than four places by modifying the MAX_DIGITS variable; however, one 
          must also make sure to update the global for RANGE as well to correctly reflect the max range as
          to maintain the max place for the numbers when they get randomly initialized.

          Currently, I have RADIX-SORT iterating through the places by increasing the exponent on 10.
          Say we want four digit numbers to be sorted, I first evaluate the max power of 10 that
          encompasses the greatest digit place: in all cases it will be one less than the desired number of
          digits. For five digit numbers, the max power of 10 to encompass the greatest digit place is 4:
          
          10^(4)= 10,000

          With that value I can then increment the exponent on 10 to get through each place:

          10^(0) yields the unit place
          10^(1) yields the tens place
          10^(2) yields the hundreds place

          I also calculate the next power of 10 which violates the max allotted number of places. For 4 digit
          numbers, the exponent of 4 will be too many:
          
          10^(4)= 10,000

          With the above, we go one place too far and evaluate a place that does not exist with out set of numbers.
          That is fine however, because this calculation is useful because with this value, whilst iterating
          through the places, once our iterator reaches this point, we know to stop and the data is sorted.

*/


#include <iostream>
#include <cstdlib>
#include <memory>
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
    // 3             C[i] = 0
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
    
    std::unique_ptr<int[]> C; // Declaring a smart pointer, unique_ptr, to manage the dynamic array
        
    try {
        C = std::make_unique<int[]>(RANGE); // Allocate memory for C dynamically (on the heap) | Auto deletes when out of scope
    }
    catch (const std::bad_alloc& e) {
        // Handle failures
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    }

    // RANGE acts as K: if max number goes up to 7, the range is 8 (0-7).
    for (int i = 0; i < RANGE; i++) {
        C[i] = 0;
    }

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
