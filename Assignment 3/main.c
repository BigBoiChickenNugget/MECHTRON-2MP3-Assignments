#include "utility.h"

void main() {

    WordData *data = read_data("vader_lexicon.txt");

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

	for (int i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
		float score = calculate_sentiment_score(data, sentences[i]);
		printf("Sentence:\n%s\nCompound: %f\n\n", sentences[i], score);
	}

	free(data);
}
