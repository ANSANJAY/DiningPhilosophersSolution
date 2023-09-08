/* 
 * Implementation of the Dining Philosophers problem.
 * The goal is to prevent deadlocks and ensure every philosopher gets to eat.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "dining_philospher_struct.h"

#define N_PHILOSOPHER	5  // Number of philosophers

static phil_t phil[N_PHILOSOPHER];  // Array of philosopher structures
static spoon_t spoon[N_PHILOSOPHER];  // Array of spoon structures

/* 
 * Retrieve the right spoon for the given philosopher.
 */
static spoon_t *phil_get_right_spoon(phil_t *phil) {
	int phil_id = phil->phil_id;

	if (phil_id == 0) {
		return &spoon[N_PHILOSOPHER -1];
	}
	return &spoon[phil_id - 1];
}

/* 
 * Retrieve the left spoon for the given philosopher.
 */
static spoon_t *phil_get_left_spoon(phil_t *phil) {
	return &spoon[phil->phil_id];
}

/* 
 * The main function where a philosopher eats.
 * It ensures that the philosopher eats using the correct pair of spoons.
 */
void phil_eat(phil_t *phil) {
	spoon_t *left_spoon = phil_get_left_spoon(phil);
	spoon_t *right_spoon = phil_get_right_spoon(phil);

	// Validations to ensure philosopher eats with the correct spoons
	assert(left_spoon->phil == phil);
	assert(right_spoon->phil == phil);
	assert(left_spoon->is_used == true);
	assert(right_spoon->is_used == true);

	phil->eat_count++;
	printf("Phil %d eats with spoon [%d, %d] for %d times\n",
		phil->phil_id, left_spoon->spoon_id, right_spoon->spoon_id,
		phil->eat_count);
	sleep(1); // Let the philosopher enjoy his meal for a second
}

/* 
 * Release the spoons once a philosopher has finished eating.
 */
void philosopher_release_both_spoons(phil_t *phil) {
	spoon_t *left_spoon  = phil_get_left_spoon(phil);
	spoon_t *right_spoon = phil_get_right_spoon(phil);

	pthread_mutex_lock(&left_spoon->mutex);
	pthread_mutex_lock(&right_spoon->mutex);

	// Validation to ensure correctness before releasing the spoons
	assert(left_spoon->phil == phil);
	assert(left_spoon->is_used == true);
	assert(right_spoon->phil == phil);
	assert(right_spoon->is_used == true);

	// Release left spoon
	printf("phil %d releasing the left spoon %d\n", phil->phil_id, left_spoon->spoon_id);
	left_spoon->phil = NULL;
	left_spoon->is_used = false;
	pthread_cond_signal(&left_spoon->cv);
	pthread_mutex_unlock(&left_spoon->mutex);

	// Release right spoon
	printf("phil %d releasing the right spoon %d\n", phil->phil_id, right_spoon->spoon_id);
	right_spoon->phil = NULL;
	right_spoon->is_used = false;
	pthread_cond_signal(&right_spoon->cv);
	pthread_mutex_unlock(&right_spoon->mutex);
}

/* 
 * A function to help a philosopher get both spoons before eating.
 * Ensures safe acquisition of spoons without causing deadlocks.
 */
bool philosopher_get_access_both_spoons(phil_t *phil) {
	spoon_t *left_spoon  = phil_get_left_spoon(phil);
	spoon_t *right_spoon = phil_get_right_spoon(phil);

	// Try to acquire left spoon
	pthread_mutex_lock(&left_spoon->mutex);
	// Wait if left spoon is used by another philosopher
	while(left_spoon->is_used && left_spoon->phil != phil) {
		pthread_cond_wait(&left_spoon->cv, &left_spoon->mutex);
	}
	left_spoon->is_used = true;
	left_spoon->phil = phil;
	pthread_mutex_unlock(&left_spoon->mutex);

	// Try to acquire right spoon
	pthread_mutex_lock(&right_spoon->mutex);
	if (right_spoon->is_used == false) {
		right_spoon->is_used = true;
		right_spoon->phil = phil;
		pthread_mutex_unlock(&right_spoon->mutex);
		return true;
	}
	// If failed to get right spoon, release the left spoon
	else {
		if (right_spoon->phil != phil) {
			pthread_mutex_lock(&left_spoon->mutex);
			left_spoon->is_used = false;
			left_spoon->phil = NULL;
			pthread_mutex_unlock(&left_spoon->mutex);
			pthread_mutex_unlock(&right_spoon->mutex);
			return false;
		}
		else {
			pthread_mutex_unlock(&right_spoon->mutex);
			return true;
		}
	}
}

/* 
 * Main function for each philosopher thread.
 * Each philosopher tries to get spoons and eat in a loop.
 */
void * philosopher_fn(void *arg) {
	phil_t *phil = (phil_t *)arg;

	while(1) {
		if (philosopher_get_access_both_spoons(phil)) {
			phil_eat(phil);
			philosopher_release_both_spoons(phil);
			sleep(1);
		}
	}
}

/* 
 * Main function
 * Initializes philosophers and spoons and starts the philosophers' threads.
 */
int main(int argc, char **argv) {
	int i = 0;
	pthread_attr_t attr;

	// Initialize all spoons
	for ( i = 0; i < N_PHILOSOPHER; i++ ) {
		spoon[i].spoon_id = i;
		spoon[i].is_used = false;
		spoon[i].phil = NULL;
		pthread_mutex_init(&spoon[i].mutex, NULL);
		pthread_cond_init(&spoon[i].cv, NULL);
	}

	// Initialize all philosophers and create threads for each one
	pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	/* create philosopher threads */
	for ( i = 0; i < N_PHILOSOPHER; i++) {
		phil[i].phil_id = i;
		phil[i].eat_count = 0;
		pthread_create(&phil[i].thread_handle, &attr, philosopher_fn, &phil[i]);
	}
	
	pthread_exit(0);
	return 0;
}

