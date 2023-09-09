## Dining Philosophers Problem 📝

### Introduction 📖

- The **Dining Philosophers** problem is a classic synchronization problem that revolves around ensuring multiple entities (philosophers) can safely access shared resources (spoons) without causing deadlocks or race conditions.
  
### Functions in Focus 🕵️

1. `philosopher_function`
   
```C
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
```

2. `philosopher_get_access_both_spoons`

```C
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

```
3. `philosopher_release_both_spoons`

```C
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

```


### Key Logics to Implement 🧠

#### 1. Assigning a Spoon `s` to Philosopher `P` 🍴

- When philosopher `P` wants to get access to spoon `s`:
    ```pseudo
    Lock mutex of spoon s
    Mark spoon s as used (is_used = true)
    Set philosopher pointer to philosopher P
    Unlock mutex of spoon s
    ```
    - **Rationale**: Locking the mutex ensures that while the state of the spoon is being changed, no other thread can access or modify its state, thereby preventing race conditions.

#### 2. Making a Spoon Available again 🔄

- If a spoon is occupied by a philosopher and needs to be released:
    ```pseudo
    Lock mutex of spoon s
    Mark spoon s as not used (is_used = false)
    Set philosopher pointer to null
    Unlock mutex of spoon s
    ```
    - **Rationale**: This logic ensures that the spoon is safely marked as available for other philosophers.

### Implementation Pointers 💡

1. **Concurrency & Safety**: Always lock the mutex of a resource (spoon in this case) when intending to modify or check its state. This ensures that concurrent accesses do not lead to inconsistent states.
2. **Availability Check**: Before accessing a resource, always check its availability status. This ensures that deadlocks and other synchronization issues do not arise.
3. **Simplicity**: The solution's backbone revolves around the simple logic of acquiring and releasing resources safely in a multithreaded environment.

---

## Interview Questions & Answers 🤔💬

1. **Q**: What is the main challenge posed by the Dining Philosophers problem?
   - **A**: The Dining Philosophers problem illustrates the challenges of ensuring multiple entities can safely access shared resources without causing deadlocks or race conditions.

2. **Q**: Why do we need to lock the mutex of the spoon when trying to access or modify its state?
   - **A**: Locking the mutex ensures that while the state of the resource is being modified or accessed, no other thread can intervene, preventing race conditions and ensuring data integrity.

3. **Q**: Can you explain what a deadlock is in the context of the Dining Philosophers problem?
   - **A**: A deadlock in the Dining Philosophers context would occur if every philosopher picked up one spoon and waited indefinitely for the second one, making it impossible for any philosopher to eat.

4. **Q**: How does marking a spoon as 'not used' help in solving the Dining Philosophers problem?
   - **A**: By marking a spoon as 'not used', it signifies that the spoon is available for another philosopher to use. This allows philosophers to know when they can safely try to acquire a spoon without causing contention.

5. **Q**: Why is the problem called 'Dining Philosophers'?
   - **A**: The problem is a metaphor for philosophers (entities) who think and eat (two actions that require resources). They need two spoons (resources) to eat, representing the challenge of resource allocation and concurrency in computer systems.

---

I hope these notes help you in your interview preparation! Good luck! 🍀🌟
