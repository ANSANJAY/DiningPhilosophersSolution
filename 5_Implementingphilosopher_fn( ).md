# DiningPhilosophersSolution
An implementation of the Dining Philosophers problem, focusing on concurrency control via mutexes and semaphores. This repo demonstrates how to manage multiple processes accessing shared resources, aiming to solve issues of deadlock and contention. Includes code examples and a guide.

## Philosopher Function Implementation  📝

### Introduction 📖

- We're delving into the core implementation of the **Philosopher Function** in the Dining Philosophers problem.
  
### Function Overview 🕵️

- The `philosopher_function` is the **starting point** of the solution.
- It serves as a **thread function**, meaning each thread (representing a philosopher) will concurrently execute within this function.

### Arguments and Setup 🔧

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

- The function takes an **argument**: a pointer to the philosopher.
    ```pseudo
    Argument -> philosopher_pointer
    Typecast -> Philosopher_type philosopher_pointer
    ```

### Infinite Loop and Logic 🔄

1. The thread executes within an **infinite loop** (`while(1)`), indicating that the philosopher will continuously try to eat.
   
2. A **high-level API** (`philosopher_get_access_both_spoons`) is invoked to check if a philosopher can acquire both spoons.
    ```pseudo
    if (philosopher_get_access_both_spoons(philosopher_pointer)) {
        // Philosopher gets both spoons
    }
    ```

3. **Inside the `if` block**:
    - The philosopher has successfully acquired both spoons.
    - The philosopher then proceeds to **enjoy a meal** (`philosopher_eat`), which has a `sleep(1)` built in. This simulates the philosopher eating for one second.
   
4. **Post eating**:
    - The philosopher releases the spoons using the `philosopher_release_both_spoons` API. This ensures the spoons are available for others.
    - Thereafter, the philosopher goes into a `sleep(1)` state, abiding by the problem's constraints, before trying to acquire the spoons again.


## Interview Questions & Answers 🤔💬

1. **Q**: What is the role of the `philosopher_function` in the Dining Philosophers problem?
   - **A**: The `philosopher_function` is the primary thread function where each philosopher (thread) tries to acquire spoons, eat, and then release the spoons in a continuous loop.

2. **Q**: Why is there an infinite loop (`while(1)`) in the philosopher function?
   - **A**: The infinite loop simulates the continuous attempts of each philosopher to eat, mimicking the ongoing nature of the problem.

3. **Q**: How does the solution ensure that a philosopher waits after eating before trying to acquire the spoons again?
   - **A**: After releasing the spoons post-eating, the philosopher goes into a `sleep(1)` state for a second before the next attempt, adhering to the problem's constraints.

4. **Q**: Why is abstraction important in solving the Dining Philosophers problem, especially in multithreaded programming?
   - **A**: Abstraction allows us to break down the problem into simpler, modular parts (like the supporting APIs). This makes the code more readable, organized, and easier to manage, especially in complex multithreaded scenarios.

5. **Q**: In the `philosopher_function`, what does the API `philosopher_get_access_both_spoons` do?
   - **A**: The `philosopher_get_access_both_spoons` API checks and tries to allow a philosopher to acquire both spoons. If successful, it returns `true`, indicating the philosopher can now eat.

- Remember to understand the underlying concepts and logic behind the problem. 🍀🌟
