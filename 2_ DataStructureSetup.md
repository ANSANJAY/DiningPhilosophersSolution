# Dining Philosopher Problem: Data Structures 🍴🤔

In the Dining Philosopher problem, interaction primarily occurs between two objects: `Philosophers` and `Spoons`. The data structures that represent these entities play a crucial role in solving the problem.

## 1. Philosopher Data Structure 🧑

### Fields:

- **Philosopher ID:** Each philosopher is assigned a unique ID. For instance, the identifiers could be `Ph0`, `Ph1`, `Ph2`, etc. 
  - **Purpose:** Uniquely identify each philosopher.

- **Thread Handle:** Philosophers are modeled as threads. 
  - **Purpose:** Handle the thread associated with each philosopher.

- **Eat Count:** Tracks the number of times a philosopher has successfully accessed both spoons to eat.
  - **Purpose:** Monitor how many times a philosopher enjoys the cake after obtaining both spoons.

```C
typedef struct phil_ {

	int phil_id;
	pthread_t thread_handle;
	int eat_count;
} phil_t;

```
## 2. Spoon Data Structure 🥄

### Fields:

- **Spoon ID:** Each spoon has a unique identifier, e.g., `SP0`, `SP1`, `SP2`, and so on.
  - **Purpose:** Uniquely identify each spoon.

- **Is Used (Boolean):** Indicates whether a spoon is in use.
  - **Purpose:** Determine the availability of a spoon. If a philosopher is using it, this will be `true`, otherwise `false`.

- **Philosopher Pointer:** Points to the philosopher that is currently using the spoon, if any.
  - **Purpose:** Identify which philosopher is currently using the spoon. If no philosopher is using it, this pointer is set to `null`.

- **Mutex and Condition Variable:** Since the spoon is a shared resource, it requires synchronization mechanisms.
  - **Purpose:** Ensure safe and synchronized access to the spoon resource.
 
    ```C
    
    typedef struct spoon_ {

	int spoon_id;
	bool is_used;	/* bool to indicate if the spoon is being used or not */
	phil_t *phil;	/* If used, then which philosopher is using it */
	pthread_mutex_t mutex; /* For Mutual Exclusion */
	pthread_cond_t cv;	/* For thread Co-ordination competing for this Resource */
} spoon_t;

    
    ```

> All these data structures are defined in the header file `dining_philosopher_struct.h`.

---

##  Questions 📝

1. **Q:** Describe the purpose of the `Eat Count` in the Philosopher data structure.
   **A:** The `Eat Count` tracks the number of times a philosopher has successfully accessed both spoons and eaten. It monitors how often a philosopher enjoys the cake.

2. **Q:** In the Spoon data structure, what does the `Philosopher Pointer` represent?
   **A:** The `Philosopher Pointer` points to the philosopher that is currently using the spoon. If no philosopher is using the spoon, this pointer is set to `null`.

3. **Q:** Why does the **Spoon** data structure need a Mutex and Condition Variable?
   **A:** The spoon, being a shared resource among philosophers, requires synchronization mechanisms to ensure it is accessed safely and without causing race conditions. Mutex and Condition Variables help in achieving this synchronization.

4. **Q:** How is a philosopher represented in the Dining Philosopher problem?
   **A:** In the Dining Philosopher problem, each philosopher is modeled as a thread, with a unique `Philosopher ID` and an `Eat Count` to monitor how many times they have eaten.

5. **Q:** What would the state of the `Is Used` field and the `Philosopher Pointer` be if a spoon is not currently in use?
   **A:** If a spoon is not in use, the `Is Used` field would be `false`, and the `Philosopher Pointer` would be set to `null`.

---

This document provides a detailed breakdown of the data structures involved in the Dining Philosopher problem. A comprehensive understanding of these structures is crucial for solving the problem effectively. 📘🔍🍝
