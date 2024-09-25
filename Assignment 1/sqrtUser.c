#include <stdio.h>

// Function prototype
double sqrtUser(double number, int n);

int main() {

	// Loop to continue asking for user input and computing the square root
	while (1) {

		// Variables to store user input
		double number;
		int n;

		// Ask for the number the user wants to find the square root of
		printf("Enter a number: ");
		scanf("%lf", &number);

		// Ask for the number of iterations the user wants to use
		printf("Enter the number of decimal places: ");
		scanf("%d", &n);

		// Print the result
		printf("The square root of %lf is %.10f\n\n", number, sqrtUser(number, n));
	}
}

// Function to compute the square root of a number using the Newton-Raphson method
double sqrtUser(double number, int n) {

	double accuracy = 1;
	for (int i = 1; i < n; i++) {
		accuracy /= 10;
	}

	double estimate = number / 2; 
	double estimate_next = number;

	while (1) {
		// First compute f(x) = x^2 - number where x = guess
		double f = estimate*estimate - number;

		// Now compute f'(x) = 2x where x = guess
		double f_prime = 2*estimate;

		estimate_next = estimate - f/f_prime;
		/*printf("Initial estimate: %lf\n", estimate);*/
		/*printf("Estimate: %lf\n", estimate_next);*/
		/*printf("f: %lf\n", f);*/
		/*printf("f_prime: %lf\n", f_prime);*/
		/*printf("Accuracy: %lf\n", accuracy);*/

		if (estimate-estimate_next > accuracy || estimate_next-estimate > accuracy) {
			estimate = estimate_next;
		}
		else {
			break;
		}

		/*break;*/
	}

	return estimate_next;
}
