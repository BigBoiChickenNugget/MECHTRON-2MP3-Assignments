// CODE: include necessary library(s)
#include <stdio.h>
#include <string.h>
#include "mySort.c"

// Utility functions
void printArray(int arr[], int n);


// Test the sorting algorithms
int main() {
    /*int arr[] = {64, 64, -134, -5, 0, 25, 12, 22, 11, 90, -500};*/
	/*int arr[] = {9, 4, 3, 8, 10, 2, 5};*/
	/*int arr[] = {3, 9, 2, 1, 4, 5};*/
	/*int arr[] = {15, 30, 10, 5, 20, 25, 8, 3, 2, 18, 6};*/

int arr[] = {
        -12, 45, 0, -7, 23, -15, 9, 76, -30, 42,
        58, -3, 0, 19, 21, -1, 34, -100, 55, 2,
        30, -25, 0, 77, -5, 16, -12, 88, 10, -40,
        22, -60, 49, 0, 5, 99, -75, 14, 33, 57,
        0, -33, 91, -9, 38, 7, 4, 12, -1, 18
    };


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
	mergeSort(testArr, n/2, n - n/2); // Takes care of odd lengths automatically
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

    return 0;
}

// Helper functions
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

