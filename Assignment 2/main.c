// CODE: include necessary library(s)
#include <stdio.h>
#include <string.h>
#include "mySort.h"

// Utility functions
void printArray(int arr[], int n);


// Test the sorting algorithms
int main() {
    /*int arr[] = {64, 64, -134, -5, 0, 25, 12, 22, 11, 90, -500};*/
	/*int arr[] = {9, 4, 3, 8, 10, 2, 5};*/
	/*int arr[] = {3, 9, 2, 1, 4, 5};*/
	int arr[] = {15, 8, -465, -500, 8, 18, 18, 30, 10, 5, 20, 25, 8, 3, 2, 18, 6, -28, -40, -465};
	/*int arr[] = {1, 99, 56, 87, 322, 34, 2175, 217, 8};*/
	/*int arr[] = {-1};*/

	int n = sizeof(arr) / sizeof(arr[0]);

	int testArr[n];

	// Bubble Sort
	memcpy(testArr, arr, n * sizeof(int));
	printf("Original array: ");
    printArray(testArr, n);
    bubbleSort(testArr, n);
    printf("Bubble sorted array: ");
    printArray(testArr, n);
	printf("\n");

    // CODE: do the same test cases for Insertion Sort, Merge Sort, Heap Sort, Counting Sort
    // You will submit main.c, and your project will be marked based on main.c as well
	
    // Insertion Sort
	memcpy(testArr, arr, n * sizeof(int));
	printf("Original array: ");
	printArray(testArr, n);
	insertionSort(testArr, n);
	printf("Insertion sorted array: ");
	printArray(testArr, n);
	printf("\n");

	// Merge sort
	memcpy(testArr, arr, n * sizeof(int));
	printf("Original array: ");
	printArray(testArr, n);
	mergeSort(testArr, 0, n-1);
	printf("Merge sorted array: ");
	printArray(testArr, n);
	printf("\n");
    
	// Heap sort
	memcpy(testArr, arr, n * sizeof(int));
	printf("Original array: ");
	printArray(testArr, n);
	heapSort(testArr, n);
	printf("Heap sorted array: ");
	printArray(testArr, n);
	printf("\n");

	// Counting sort
	memcpy(testArr, arr, n * sizeof(int));
	printf("Original array: ");
	printArray(testArr, n);
	countingSort(testArr, n);
	printf("Counting sorted array: ");
	printArray(testArr, n);
	printf("\n");
	

    return 0;
}

// Helper functions
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

