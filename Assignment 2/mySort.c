// CODE: include necessary library(s)
// you have to write all the functions and algorithms from scratch,
// You will submit this file, mySort.c holds the actual implementation of sorting functions
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

// CODE: implement the algorithms for Insertion Sort, Merge Sort, Heap Sort, Counting Sort

// Insertion Sort
void insertionSort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) { 
		int *lowest = &arr[i];
		for (int j = i+1; j < n; j++) {
			if (arr[j] < *lowest) swap(&arr[j], lowest);

		}
	}
}

// Merge Sort. Given an array and the length of the left and right halves.
void mergeSort(int arr[], int l, int r) {

	// Base case is when only one element is in the array so one or the other half is 0.
	if (l == 0 || r == 0) return;

	// Recursively split the array up
	mergeSort(&arr[0], l/2, l - l/2); // l - l/2 is to take care of odd numbers easily.
	mergeSort(&arr[l], r/2, r - r/2); // Start of the right half should be end at the index which is the number of left half elements

	// Temporary array to store the sorted result of the left and right arrays.
	int tmp[l+r];

	// Stores the indexes of the array halves
	int indexSortedL = 0;
	int indexSortedR = l;

	// To check if either half is empty
	bool depletedR = false;
	bool depletedL = false;

	// Iterate through the entire tmp array and assign the lesser value between the left and right half
	for (int i = 0; i < l+r; i++) {

		// If the current left element is less than the current right element, or if the right array has been used up, go ahead and insert into tmp
		if ((arr[indexSortedL] <= arr[indexSortedR] || depletedR == true) && !depletedL) {
			tmp[i] = arr[indexSortedL];
			indexSortedL++;

			// If all the elements have been used up make the corresponding boolean true
			if (indexSortedL >= l) {
				depletedL = true;
				indexSortedL = l-1; // To ensure no unsafe memory access
			}	
		}

		// If the current right element is less than the current left element, or if the left half has been used up, insert the right element into tmp
		else if (arr[indexSortedR] < arr[indexSortedL] || depletedL == true) {
			tmp[i] = arr[indexSortedR];
			indexSortedR++;

			// If all the right elements have been used up make the corresponding boolean true
			if (indexSortedR >= l+r) {
				depletedR = true;
				indexSortedR = r+l-1; // To ensure no unsafe memory access
			}
		}
	}

	// Replace arr with tmp
	memcpy(arr, tmp, sizeof(tmp));
}

void heapSort(int arr[], int n) {

	// Keep going we've extracted all the elements
	for (int i = n-1; i >= 0; i--) {

		// Ensure max heap is made
		for (int j = 1; j <= i; j++) {
			
			// If the parent is smaller than a child node, swap them
			// While loop because the swapped may be smaller than another child node so keep checking
			while (arr[(j-1) / 2] < arr[j]) {
				swap(&arr[(j-1) / 2], &arr[j]);

				// Move back to the swapped parent to ensure that it's also sorted
				j = ((j-1) / 2);
			}
		}

		swap(&arr[0], &arr[i]);
	}
}

void countingSort(int arr[], int n) {

	// Find the maximum value in the array
	int max = arr[0];
	int min = arr[0]; // Also get minimum so we can deal with negatives
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) max = arr[i];
	}

	// Declare an array of counts with max elements
	int *counts = malloc((fabs(min)+max+1)*sizeof(int));
	for (int i = 0; i < n; i++) {

		// Increment the number of counts for whatever element is in the array
		counts[arr[i]+fabs(min)]++;
	}

	// Go through the array and put the number of counts in at each position
	int index = 0;
	for (int i = 0; i <= max; i++) {
		for (int j = 0; j < counts[i]; j++) {
			arr[index] = i;
			index++;
		}
	}
	free(counts);
}
