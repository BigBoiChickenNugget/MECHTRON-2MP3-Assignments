#include "utility.h"

// Example of how to use read_data in main
int main() {

    WordData *data = read_data("vader_lexicon.txt");

	for (int i = 0;data[i].word[0] != '\0'; i++) {
		printf("%s\t%f\t%f\t", data[i].word, data[i].value1, data[i].value2);
		for (int j = 0; j < ARRAY_SIZE; j++) {
			printf("%d ", data[i].intArray[j]);
		}
		printf("\n");
	}

	printf("\n");

	free(data);
}

WordData* read_data(char *filename) {

    // Open the file
    FILE *file = fopen(filename, "r");

    // Ensure the file was successfully opened
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    // Allocate memory for the first block of WordData
    WordData *data = malloc(sizeof(WordData));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    int i = 0;

    // Read data from the file
    while (1) {

		// Allocate memory for the WordData item
		data = realloc(data, (i+1) * sizeof(WordData));

		// Ensure memory was allocated
		if (data == NULL) {
			printf("Memory allocation failed\n");
			free(data);
			fclose(file);
			return NULL;
		}

        // Read the word and two float values
        fscanf(file, "%s %f %f", &data[i].word, &data[i].value1, &data[i].value2);

		// Break if end of file
		if (feof(file)) {
			data[i].word[0] = '\0';
			break;
		}

        // Read the integer array
        char line[2000];
        fgets(line, 2000, file);  // Read the line for integers

		/*printf("WORD: %s\n", (*data)[i].word);*/
		/*printf("LINE: %s\n", line);*/
        char *token = strtok(line, "[], \n\t\v\f\r");

        for (int j = 0; j < ARRAY_SIZE && token != NULL; j++) {
            data[i].intArray[j] = atoi(token);
            token = strtok(NULL, "[], \n\t\v\f\r");
        }


        // Prepare to read the next WordData item
        i++;

    }

    // Close the file
    fclose(file);

	// Return the data
	return data;
}
