#include "utility.h"

void main() {

	// Get the data from the file
    WordData *data = read_data("vader_lexicon.txt");

	// Testcases
	char *sentences[] = {
		"VADER is smart, handsome, and funny.",
		"VADER is smart, handsome, and funny!",
		"VADER is very smart, handsome, and funny.",
		"VADER is VERY SMART, handsome, and FUNNY.",
		"VADER is VERY SMART, handsome, and FUNNY!!!",
		"VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!",
		"VADER is not smart, handsome, nor funny.",
		"At least it isn't a horrible book.",
		"The plot was good, but the characters are uncompelling and the dialog is not great.",
		"Make sure you :) or :D today!",
		"Not bad at all",
	};

	// Iterate through the testcases and output the sentiment score, positive sentiment, neutral sentiment, and negative sentiment
	for (int i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
		float *score = calculate_sentiment_score(data, sentences[i]);
		printf("Sentence:\n%s\n", sentences[i]);
		printf("Sentiment score: %f\n", *score);
		printf("Positive sentiment: %f\n", *(score + 1));
		printf("Neutral sentiment: %f\n", *(score + 2));
		printf("Negative sentiment: %f\n\n", *(score + 3));
		
		// Free the memory allocated for the score
		free(score);
	}

	// Free the memory allocated for the data
	free(data);
}
