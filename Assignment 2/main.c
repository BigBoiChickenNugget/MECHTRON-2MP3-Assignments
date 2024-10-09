// CODE: include necessary library(s)
#include <stdio.h>
#include <string.h>
#include "mySort.c"

// Utility functions
void printArray(int arr[], int n);


// Test the sorting algorithms
int main() {
    /*int arr[] = {64, -134, -5, 0, 25, 12, 22, 11, 90};*/

	int arr[150] = {
		23, 45, 12, 78, 56, 89, 34, 67, 90, 11,
		54, 32, 87, 66, 41, 73, 14, 19, 29, 36,
		21, 8, 5, 17, 40, 82, 99, 60, 33, 25,
		15, 49, 71, 2, 39, 91, 27, 22, 86, 70,
		1, 64, 4, 50, 44, 18, 48, 88, 100, 72,
		75, 42, 77, 93, 37, 63, 83, 9, 30, 65,
		81, 58, 3, 61, 24, 94, 97, 55, 76, 13,
		74, 16, 7, 80, 52, 69, 10, 95, 68, 46,
		38, 99, 47, 84, 92, 20, 35, 26, 59, 57,
		65, 14, 31, 8, 72, 100, 77, 21, 19, 39,
		46, 83, 65, 29, 3, 41, 74, 57, 81, 12,
		18, 22, 67, 95, 42, 50, 13, 66, 44, 7
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
	mergeSort(testArr, n);
	printf("Insertion sorted array: ");
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

