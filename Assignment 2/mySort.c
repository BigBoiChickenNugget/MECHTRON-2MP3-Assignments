// CODE: include necessary library(s)
// you have to write all the functions and algorithms from scratch,
// You will submit this file, mySort.c holds the actual implementation of sorting functions
#include <math.h>
#include <stdbool.h>


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

// Merge Sort
void mergeSort(int arr[], int n) {

	// Base case
	if (n == 1) return;

	int lenLeft = n/2;
	int lenRight = n/2;

	// If array length is odd the right half has an extra element.
	if (n % 2 != 0) lenRight = n/2 + 1;

	// Recursively split the array up
	mergeSort(&arr[0], lenLeft);
	mergeSort(&arr[lenLeft], lenRight);

	/*printf("Presort left:");*/
	/*for (int i = 0; i < lenLeft; i++) {*/
	/*	printf(" %d", arr[i]);*/
	/*}*/
	/**/
	/*printf("\nPresort right:");*/
	/*for (int i = lenLeft; i < lenRight+lenLeft; i++) {*/
	/*	printf(" %d", arr[i]);*/
	/*}*/
	/*printf("\n");*/

	// Temporary array to store the sorted result of the left and right arrays.
	int tmp[lenLeft+lenRight];

	// Stores the indexes of the array halves
	int indexSortedL = 0;
	int indexSortedR = lenLeft;

	bool depletedR = false;
	bool depletedL = false;

	for (int i = 0; i < lenLeft+lenRight; i++) {

		if ((arr[indexSortedL] <= arr[indexSortedR] || depletedR == true) && !depletedL) {
			tmp[i] = arr[indexSortedL];
			indexSortedL++;
			if (indexSortedL >= lenLeft) {
				depletedL = true;
				indexSortedL = lenLeft-1; // To ensure no unsafe memory access
			}	
		}

		else if (arr[indexSortedR] < arr[indexSortedL] || depletedL == true) {
			tmp[i] = arr[indexSortedR];
			indexSortedR++;
			if (indexSortedR >= lenRight+lenLeft) {
				depletedR = true;
				indexSortedR = lenRight+lenLeft-1;
			}
		}
	}

	memcpy(arr, tmp, sizeof(tmp));
	/*printf("Current status: ");*/
	/*for (int i = 0; i < n; i++) {*/
	/*	printf(" %d", arr[i]);*/
	/*}*/
	/*printf("\n");*/
}

