#include "utility.h"

WordData* read_data(char *filename) {

    // Open the file
    FILE *file = fopen(filename, "r");

    // Ensure the file was successfully opened
    if (file == NULL) {
        printf("Error opening file\n");
		exit(1);
    }

    // Allocate memory for the first block of WordData
    WordData *data = malloc(sizeof(WordData));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
		exit(1);
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
			exit(1);
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

// Linear search for a word in the WordData array
WordData find_data(WordData *data, char *word) {

	// Search for the word in the data array
	for (int i = 0; data[i].word[0] != '\0'; i++) {
		if (strcmp(data[i].word, word) == 0) {
			return data[i];
		}
	}

	// Return a WordData item with a null word if word not found
	WordData nullData;
	nullData.word[0] = '\0';
	return nullData;
}

// Function to calculate the sentiment score of a sentence
float *calculate_sentiment_score(WordData *data, char *sentence) {

	// Scores array
	float scores[MAX_STRING_LENGTH];

	// Count of all words with sentiment
	int sentimentCount = 0;

	// Sum of all sentiment scores
	float sentimentSum = 0.0;

	// Variables to store calculations for pos, neu, neg
	float pos = 0.0;
	float neu = 0.0;
	float neg = 0.0;

	// Stores the current intensifier values
	float intensifier = 0;

	// Stores the current negation value
	float negation = 0;

	// Array to store the split sentence
	char sentence_split[MAX_STRING_LENGTH][MAX_STRING_LENGTH];

	// Copy the sentence for strtok to work
	char sentence_copy[MAX_STRING_LENGTH];
	strcpy(sentence_copy, sentence);

	// Since the only punctuation we care about is exclamation marks
	// We will remove all other punctuation
	char *token = strtok(sentence_copy, " \n\t\v\f\r,.?");

	// Loop through the tokens
	for (int index = 0; token != NULL; index++) {

		// Booleans to check for all caps and exclamations
		bool allCaps = true;
		int exclamation = 0;

		// Convert the token to lowercase
		char currWord[MAX_STRING_LENGTH];
		strcpy(currWord, token);

		// Iterate through each character and use tolower()
		for (int i = 0; currWord[i] != '\0'; i++) {

			// Check for all uppercase and ensure exclamation marks are not counted
			if (islower(currWord[i]) && currWord[i] != '!') allCaps = false;

			// Convert to lowercase
			currWord[i] = tolower(currWord[i]);

			// Check for exclamation marks
			if (currWord[i] == '!') {

				// Increment the exclamation count and null the character
				exclamation++;
				currWord[i] = '\0';

				// Limit the exclamation count to 3
				if (exclamation > 3) exclamation = 3;

			}
		}

		// Copy the token to the sentence split array
		strcpy(sentence_split[index], currWord);

		// Find the word in the data array
		WordData wordData = find_data(data, currWord);

		// Check if the word was found
		if (wordData.word[0] != '\0') {

			// Increment the sentiment count
			sentimentCount++;

			// Add the score to the scores array
			scores[index] = wordData.value1;

			// If word is capitalized, multiply by factor
			if (allCaps) {
				scores[index] *= CAPS;
			}

			// Add intensifier and negation values
			if (intensifier != 0) scores[index] += intensifier * scores[index];
			if (negation != 0) scores[index] *= negation;

			// Add exclamation mark if positive, and subtract if negative
			// Only works if the current word is a sentiment word
			if (scores[index] > 0) {
				scores[index] += exclamation * scores[index] * EXCLAMATION;
			} else {
				scores[index] -= exclamation * scores[index] * EXCLAMATION;
			}
			sentimentSum += scores[index];
		}

		// Reset intensifier. Negation remains until next negation word
		intensifier = 0;

		// Check if current word is an intensifier
		// Check positive intensifiers
		for (int i = 0; i < POSITIVE_INTENSIFIERS_SIZE; i++) {
			if (strcmp(sentence_split[index], positive_intensifiers[i]) == 0) {
				intensifier = INTENSIFIER;
			}
		}

		// Check negative intensifiers
		for (int i = 0; i < NEGATIVE_INTENSIFIERS_SIZE; i++) {
			if (strcmp(sentence_split[index], negative_intensifiers[i]) == 0) {
				intensifier = -INTENSIFIER;
			}
		}

		// If intensifier is capitalized, multiply by factor
		if (allCaps && intensifier != 0) {
			intensifier *= CAPS;
		}

		// Check if current word is a negation
		for (int i = 0; i < NEGATIONS_SIZE; i++) {
			if (strcmp(sentence_split[index], negation_words[i]) == 0) {
				negation = NEGATION;
			}
		}

		// If negation is capitalized, multiply by factor
		if (allCaps && negation != 0) {
			negation *= CAPS;
		}

		// Calculate pos, neu, neg
		if (scores[index] > 0) {
			pos += scores[index];
		} else if (scores[index] == 0) {
			neu += 1;
		} else {
			neg += -1 * scores[index];
		}

		// Get the next token
        token = strtok(NULL, " \n\t\v\f\r,.?");
	}

	// Calculate the compound score
	float compound = sentimentSum / sqrt( pow(sentimentSum, 2) + 15 );

	// Get the pos, neu, neg values
	float total = pos + neu + neg;
	pos = pos / total;
	neu = neu / total;
	neg = neg / total;

	// Create and return an array of the scores
	float *scoreArray = malloc(4 * sizeof(float));
	scoreArray[0] = compound;
	scoreArray[1] = pos;
	scoreArray[2] = neu;
	scoreArray[3] = neg;

	// Return the array
	return scoreArray;
}
