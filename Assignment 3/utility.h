#ifndef UTILITY_H
#define UTILITY_H

#define ARRAY_SIZE 20
#define MAX_STRING_LENGTH 20
#define LINE_LENGTH 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char word[MAX_STRING_LENGTH];
	float value1;
	float value2;
	int intArray[ARRAY_SIZE];
} WordData;

WordData *read_data(char *filename);

#endif
