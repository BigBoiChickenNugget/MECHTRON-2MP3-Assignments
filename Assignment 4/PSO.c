// CODE: include library(s)
#include "utility.h"
#include "OF_lib.h"

// Helper function to generate random numbers in a range
double random_double(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

// CODE: implement other functions here if necessary

// Function to initialize particles
void initialize_particles(Particle *particles, int NUM_PARTICLES, int NUM_VARIABLES, Bound *bounds, ObjectiveFunction objective_function) {

	for (int i = 0; i < NUM_PARTICLES; i++) {

		// Allocate memory for particle
		Particle *particle = malloc(sizeof(Particle));

		// Allocate memory for position, velocity, and best_position
		particle->position = malloc(NUM_VARIABLES * sizeof(double));
		particle->velocity = malloc(NUM_VARIABLES * sizeof(double));
		particle->best_position = malloc(NUM_VARIABLES * sizeof(double));

		// Initialize position, velocity, and best_position
		for (int j = 0; j < NUM_VARIABLES; j++) {
			particle->position[j] = random_double(bounds[j].lowerBound, bounds[j].upperBound);
			particle->velocity[j] = random_double(-1, 1);
			particle->best_position[j] = particle->position[j];
		}

		// Get the value of the particle's position
		particle->value = objective_function(particle->position, NUM_VARIABLES);

		// Set the best value to the particle's current value
		particle->best_value = particle->value;

		// Add particle to the list of particles
		particles[i] = particle;
	}
}

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    // CODE: implement pso function here
	
	// Allocate memory for particles
	Particle *particles = malloc(NUM_PARTICLES * sizeof(Particle));

	// Initialize particles
	initialize_particles(particles, NUM_PARTICLES, NUM_VARIABLES, bounds, objective_function);

	// Test by printing the particles
	for (int i = 0; i < NUM_PARTICLES; i++) {
		printf("Particle %d: ", i);
		for (int j = 0; j < NUM_VARIABLES; j++) {
			printf("%f ", particles[i]->position[j]);
		}
		printf("\n");
	}
}
