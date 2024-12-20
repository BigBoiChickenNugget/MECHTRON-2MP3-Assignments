// CODE: include necessary library(s)
// you have to write all the functions and algorithms from scratch,
// You will submit this file, mySort.c holds the actual implementation of sorting functions
#include "mySort.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

	// Iterate through each index in the array
	for (int i = 0; i < n-1; i++) { 

		// Find the lowest element in the array beyond this point and swap it with the initial point
		int *lowest = &arr[i];
		for (int j = i+1; j < n; j++) {
			if (arr[j] < *lowest) swap(&arr[j], lowest);
		}
	}
}

// Merge Sort. Given an array and the indexes of the subarray inclusive
void mergeSort(int arr[], int l, int r) {

	// Get the length of the subarray
	int n = r - l + 1;

	// Base case is when only one element is in the array
	if (n == 1) return;

	// Midpoint of the array
	int mid = (l+r) / 2;

	// Recursively split the array up
	mergeSort(arr, l, mid);
	mergeSort(arr, mid+1, r);

	// Temporary array to store the combination of the left and right arrays, both of which should be in sorted form individually
	int tmp[n];

	// Stores the indexes of the array halves
	int indexSortedL = l;
	int indexSortedR = mid+1;

	// To check if either half is empty
	bool depletedR = false;
	bool depletedL = false;

	// Iterate through the entire tmp array and assign the lesser value between the left and right half
	for (int i = 0; i < n; i++) {

		// If the current left element is less than the current right element, or if the right array has been used up, go ahead and insert into tmp
		if ((arr[indexSortedL] <= arr[indexSortedR] || depletedR == true) && !depletedL) {
			tmp[i] = arr[indexSortedL];
			indexSortedL++;

			// If all the elements have been used up make the corresponding boolean true
			if (indexSortedL > mid) {
				depletedL = true;
				indexSortedL=0; // To ensure no unsafe memory access
			}	
		}

		// If the current right element is less than the current left element, or if the left half has been used up, insert the right element into tmp
		else if (arr[indexSortedR] < arr[indexSortedL] || depletedL == true) {
			tmp[i] = arr[indexSortedR];
			indexSortedR++;

			// If all the right elements have been used up make the corresponding boolean true
			if (indexSortedR > r) {
				depletedR = true;
				indexSortedR=0; // To ensure no unsafe memory access
			}
		}
	}

	// Replace the elements in the original array with the sorted elements in the same range
	memcpy(&arr[l], tmp, n * sizeof(int));
}

// Function to make heap (used in the heapSort function)
void makeHeap(int arr[], int n, int currNodeIndex) {

	// Index of the largest amongst the parent and 2 child nodes
	int largest = currNodeIndex;

	// Get the indexes of the child nodes
	int leftChildIndex = currNodeIndex * 2 + 1;
	int rightChildIndex = currNodeIndex * 2 + 2;

	// Ensure that the left child index exists in the array
	if (leftChildIndex < n) {

		// If the left child index is greater than the existing largest (parent) assign it as the largest
		if (arr[leftChildIndex] > arr[largest]) largest = leftChildIndex;
	}

	// Ensure that the right child index is in the array
	if (rightChildIndex < n) {

		// If the right child index is greater than the existing largest (parent or left child) assign it as the largest
		if (arr[rightChildIndex] > arr[largest]) largest = rightChildIndex;
	}

	// If the largest is not the parent we started with, swap it and ensure the subheap that was swapped is still a heap
	if (largest != currNodeIndex) {
		swap(&arr[currNodeIndex], &arr[largest]);
		makeHeap(arr, n, largest);
	}
}

// Heap sort
void heapSort(int arr[], int n) {

	// Ensure we start with a max heap by going from the bottom to the top
	for (int i = n-1; i >= 0; i--) {
		makeHeap(arr, n, i);
	}

	// Begin actually sorting
	for (int i = n-1; i >= 1; i--) {

		// Swap the first and last indexes
		swap(&arr[0], &arr[i]);

		// Ensure max heap is made starting at the root node (it should be the largest)
		makeHeap(arr, i, 0);
	}
}

// Counting Sort
void countingSort(int arr[], int n) {

	// Find the maximum and minimum value in the array
	int max = arr[0];
	int min = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) max = arr[i];
		if (arr[i] < min) min = arr[i];
	}

	// Length of the counting array should be the the number of negatives plus the number of positives plus another spot for 0
	int counts[abs(min) + max + 1];

	// Initialize the array as full of zeros
	for (int i = 0; i < abs(min) + max + 1; i++) {
		counts[i] = 0;
	}

	// Count the number of each element in the array
	for (int i = 0; i < n; i++) {

		// Increment the number of counts for whatever element is in the array
		// The minimum number is added to the index to take care of negative values
		counts[arr[i]+abs(min)]++;
	}

	// Go through the possible numbers
	int index = 0;
	for (int i = min; i <= max; i++) {

		// Put the number of each element in the array in the actual array
		// The index of number has the minimum number added to it which is to take care of negative elements
		for (int j = 0; j < counts[i+abs(min)]; j++) {
			arr[index] = i;
			index++;
		}
	}
}
