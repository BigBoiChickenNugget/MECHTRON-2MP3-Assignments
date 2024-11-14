#include "utility.h"

void main() {

    WordData *data = read_data("vader_lexicon.txt");
	// char *sentence = "VADER is VERY SMART, handsome, and FUNNY!";
    char *sentence = {"Today mildly sux! But I'll get by, lol"};

	float compound = calculate_sentiment_score(data, sentence);

	printf("The compound score is: %f\n", compound);

	free(data);
}