#include "utility.h"

// Example of how to use read_data in main
int main() {
    WordData *data = NULL; // Initialize pointer to NULL

    read_data("vader_lexicon.txt", &data);

	// Show results
	for (int i = 0; i < 10; i++) {
		printf("%s\t%f\t%f\t", data[i].word, data[i].value1, data[i].value2);
		for (int j = 0; j < ARRAY_SIZE; j++) {
			printf("%d ", data[i].intArray[j]);
		}
		printf("\n");
	}

	free(data); // Free allocated memory
	return 0;
}

void read_data(char *filename, WordData **data) {

    // Open the file
    FILE *file = fopen(filename, "r");

    // Ensure the file was successfully opened
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Allocate memory for the first block of WordData
    *data = malloc(sizeof(WordData));
    if (*data == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    int i = 0;

    // Read data from the file
    while (1) {

		/*printf("I: %d\n", i);*/

        // Read the word and two float values
        fscanf(file, "%s %f %f", (*data)[i].word, &(*data)[i].value1, &(*data)[i].value2);

		// Break if end of file
		if (feof(file)) {
			break;
		}

        // Read the integer array
        char line[2000];
        fgets(line, 2000, file);  // Read the line for integers

		/*printf("WORD: %s\n", (*data)[i].word);*/
		/*printf("LINE: %s\n", line);*/
        char *token = strtok(line, "[], \n\t\v\f\r");

        for (int j = 0; j < ARRAY_SIZE && token != NULL; j++) {
            (*data)[i].intArray[j] = atoi(token);
            token = strtok(NULL, "[], \n\t\v\f\r");
        }


        // Prepare to read the next WordData item
        i++;

        // Reallocate memory to hold one more WordData entry
        WordData *temp = realloc(*data, (i + 1) * sizeof(WordData));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            free(*data);
            fclose(file);
            return;
        }

        // Update the original pointer to point to the new memory
        *data = temp;
    }

    // Close the file
    fclose(file);
}
