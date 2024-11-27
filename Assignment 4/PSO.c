// CODE: include library(s)
#include "utility.h"
#include "OF_lib.h"
#include <stdlib.h>
#include <stdio.h>

// Helper function to generate random numbers in a range
double random_double(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

// CODE: implement other functions here if necessary

// Function to initialize particles
void initialize_particles(Particle *particles, int NUM_PARTICLES, int NUM_VARIABLES, Bound *bounds, ObjectiveFunction objective_function) {

	for (int i = 0; i < NUM_PARTICLES; i++) {

		// Allocate memory for particle
		Particle particle;

		// Allocate memory for position, velocity, and best_position
		particle.position = malloc(NUM_VARIABLES * sizeof(double));
		particle.velocity = malloc(NUM_VARIABLES * sizeof(double));
		particle.best_position = malloc(NUM_VARIABLES * sizeof(double));

		// Initialize position, velocity, and best_position
		for (int j = 0; j < NUM_VARIABLES; j++) {
			particle.position[j] = random_double(bounds[j].lowerBound, bounds[j].upperBound);
			particle.velocity[j] = 0;
			particle.best_position[j] = particle.position[j];
		}

		// Get the value of the particle's position
		particle.value = objective_function(NUM_VARIABLES, particle.position);

		// Set the best value to the particle's current value
		particle.best_value = particle.value;

		// Add particle to the list of particles
		particles[i] = particle;
	}
}

// Function to update the velocity of the particles
void update(Particle *particles, int NUM_PARTICLES, int NUM_VARIABLES, double *best_position, double w, double c1, double c2, ObjectiveFunction objective_function, Bound *bounds) {

	// Get the global best value
	double global_best = objective_function(NUM_VARIABLES, best_position);

	// Update the velocity of the particle
	for (int i = 0; i < NUM_PARTICLES; i++) {

		// Update the velocity and position of the particle
		for (int j = 0; j < NUM_VARIABLES; j++) {
			particles[i].velocity[j] = w * particles[i].velocity[j] + c1 * random_double(0, 1) * (particles[i].best_position[j] - particles[i].position[j]) + c2 * random_double(0, 1) * (best_position[j] - particles[i].position[j]);

			// Update the position of the particle
			particles[i].position[j] += particles[i].velocity[j];

			// Clamp to within bounds
			if (particles[i].position[j] < bounds[j].lowerBound) {
				particles[i].position[j] = bounds[j].lowerBound;
			}
			else if (particles[i].position[j] > bounds[j].upperBound) {
				particles[i].position[j] = bounds[j].upperBound;
			}

		}

		// Update the value of the particle and the best value if necessary
		particles[i].value = objective_function(NUM_VARIABLES, particles[i].position);
		if (particles[i].value < particles[i].best_value) {

			particles[i].best_value = particles[i].value;
			for (int k = 0; k < NUM_VARIABLES; k++) {
				particles[i].best_position[k] = particles[i].position[k];
			}
		}
		
		// Update the global best value and best position if necessary
		if (particles[i].value < global_best) {
			for (int k = 0; k < NUM_VARIABLES; k++) {
				best_position[k] = particles[i].position[k];
			}
		}
	}
}

double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {

    // CODE: implement pso function here
	
	// Allocate memory for particles
	Particle *particles = malloc(NUM_PARTICLES * sizeof(Particle));

	// Initialize particles
	initialize_particles(particles, NUM_PARTICLES, NUM_VARIABLES, bounds, objective_function);

	// Set best_position to the first particle's position
	for (int i = 0; i < NUM_VARIABLES; i++) {
		best_position[i] = particles[0].position[i];
	}

	// Iterate through the maximum number of iterations
	for (int i = 0; i < MAX_ITERATIONS; i++) {

		// Update everything
		update(particles, NUM_PARTICLES, NUM_VARIABLES, best_position, 0.7, 1.5, 1.5, objective_function, bounds);
	}

	return objective_function(NUM_VARIABLES, best_position);
}
