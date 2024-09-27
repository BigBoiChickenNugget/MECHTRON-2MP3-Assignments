#include <stdio.h>

// Function prototype
double sqrtUser(double number, int n);

int main() {

	// Loop to continue asking for user input and computing the square root
	while (1) {

		// Variables to store user input
		double number;
		int n;

		// Ask for the number the user wants to find the square root of. Also check and make sure it's a number
		// Scanf returns the number of items successfully read. If it's not 1, then the user didn't enter a number and we can exit the program.
		printf("Enter a number: ");
		if (scanf("%lf", &number) != 1) {
			printf("Invalid input\n");
			return 0;
		}

		// Ask for the number of iterations the user wants to use. Also check and make sure it's a number.
		printf("Enter the number of decimal places: ");
		if (scanf("%d", &n) != 1) {
			printf("Invalid input\n");
			return 0;
		}

		// If the number is less than or equal to 0, or the number of decimal places is less than 0, then the input is invalid.
		if (number <= 0 || n < 0) {
			printf("Invalid input\n");
			return 0;
		}

		// Print the result to the user inputted number of decimal places.
		printf("The square root of %lf accurate to %d decimal places is %.*lf\n\n", number, n, n, sqrtUser(number, n));
	}
}

// Function to compute the square root of a number using the Newton-Raphson method
double sqrtUser(double number, int n) {

	// We can divide the accuracy by 10 for each decimal place we want to find
	// This gives us the allowed difference between two consecutive estimates
	double accuracy = 1;
	for (int i = 1; i < n; i++) {
		accuracy /= 10;
	}

	// Keep 2 variables for the numbers so we can find the difference between them
	double estimate = number / 2; 
	double estimate_next = number;

	// Loop to keep computing the square root until the difference between the two estimates is less than the accuracy
	while (1) {

		// Compute f(x) = x^2 - number
		double f = estimate*estimate - number;

		// Compute f'(x) = 2x
		double f_prime = 2*estimate;

		// Now compute the next estimate using the formula: x_i+1 = x_i - f(x)/f'(x)
		estimate_next = estimate - f/f_prime;

		// If the difference between the two estimates is greater than the accuracy, then update the estimate and continue
		if (estimate-estimate_next > accuracy || estimate_next-estimate > accuracy) estimate = estimate_next;

		// If the difference between the two estimates is less than the accuracy, then we have found the square root
		else break;
	}

	// Return the estimate with the correct number of ACCURATE decimal places
	return estimate_next;
}
