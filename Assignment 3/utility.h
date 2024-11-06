#ifndef UTILITY_H
#define UTILITY_H

// Define constants
#define ARRAY_SIZE 20
#define MAX_STRING_LENGTH 20
#define LINE_LENGTH 100

// Include necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the structure for the data
typedef struct {
	char word[MAX_STRING_LENGTH];
	float value1;
	float value2;
	int intArray[ARRAY_SIZE];
} WordData;

// Positive words array
char *positive_amplifiers[] = {
	"absolutely",
	"completely",
	"extremely",
	"really",
	"so",
	"totally",
	"very",
	"particularly",
	"exceptionally",
	"incredibly",
	"remarkably",
}

// Negative words array
char *negative_amplifiers[] = {
	"barely",
	"hardly",
	"scarcely",
	"somewhat",
	"mildly",
	"slightly",
	"partially",
	"fairly",
	"pretty much",
}

// The boost from exclamation marks
const float exclamation = 0.292;

// Function prototypes
WordData *read_data(char *filename); 
float calculate_sentiment_score(WordData *data, char *sentence);

#endif
