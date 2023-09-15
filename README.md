# DiningPhilosophersSolution

An implementation of the Dining Philosophers problem, focusing on concurrency control via mutexes and semaphores. This repo demonstrates how to manage multiple processes accessing shared resources, aiming to solve issues of deadlock and contention. Includes code examples and a guide.
---

# 🍽️ Dining Philosopher Problem 

This repository delves into one of the classic synchronization problems in Computer Science - The Dining Philosopher Problem. 

![](https://github.com/ANSANJAY/DiningPhilosophersSolution/blob/main/An_illustration_of_the_dining_philosophers_problem.png)

## 📌 Table of Contents

- [Introduction](#introduction)
- [Description](#diagram-description)
- [Problem Constraints](#problem-constraints)
- [Solution Approach](#solution-approach)


## 🌐 Introduction

The Dining Philosopher Problem serves as a synchronization puzzle that helps us understand challenges related to resource allocation in multi-threaded environments. This problem is usually introduced after discussing the producer-consumer problem.

## 🖼️ Description

- The setup consists of five philosophers seated around a delicious cake.
- Five spoons are placed between them, serving as the shared resources.
- A philosopher can relish the cake only if they hold both the spoons to their left and right.

## 📜 Problem Constraints

1. Philosophers require both the left and right spoons to eat.
2. The acquisition process always starts with the left spoon, followed by the right.
3. If a right spoon isn't available after securing the left, the philosopher must release the left spoon, pausing for 1 second before retrying.
4. Upon obtaining both spoons, a philosopher eats for exactly 1 second.
5. Post their meal, both spoons are released.
6. Philosophers rest for another second before reaching for the next slice.

## 🎯 Solution Approach

The core of this project revolves around:

- Representing philosophers as threads.
- Depicting spoons as shared resources.
- Creating a mechanism wherein all philosopher threads run indefinitely, ensuring concurrent eating by non-neighboring philosophers.

# Dining Philosophers Problem

This repository provides a solution to the classic synchronization problem known as the Dining Philosophers problem. Using the Pthreads library, the program ensures that all philosophers can eat without running into deadlocks or race conditions.

## Table of Contents
- [Overview](#overview)
- [Functions Breakdown](#functions-breakdown)
  - [`phil_get_right_spoon`](#phil_get_right_spoon)
  - [`phil_get_left_spoon`](#phil_get_left_spoon)
  - [`phil_eat`](#phil_eat)
  - [`philosopher_release_both_spoons`](#philosopher_release_both_spoons)
  - [`philosopher_get_access_both_spoons`](#philosopher_get_access_both_spoons)
  - [`philosopher_fn`](#philosopher_fn)
  - [`main`](#main)
  
## Overview
The Dining Philosophers problem represents `N` philosophers sitting around a round table. Each philosopher spends their time thinking and eating. For eating, they need to use two spoons - one on their left and another on their right. The challenge is to ensure all philosophers can eat without any of them getting into a deadlock.

## Functions Breakdown

### `phil_get_right_spoon`
**Purpose:** Retrieves the right spoon for a given philosopher.

**Logic:** If the philosopher is the first one (with ID `0`), their right spoon is the last spoon in the array (to simulate the circular table). Otherwise, the right spoon for a philosopher is the one with an ID one less than the philosopher's ID.

### `phil_get_left_spoon`
**Purpose:** Retrieves the left spoon for a given philosopher.

**Logic:** The left spoon for a philosopher is the one with the same ID as the philosopher.

```scss
P0 (Thread)------S0 (Resource)------P1 (Thread)
   \                                 /
    \                               /
     S4 (Resource)           S0 (Resource)
      \                           /
       \                         /
        P4 (Thread)------S4 (Resource)------P2 (Thread)
       /                         \
      /                           \
     S3 (Resource)           S1 (Resource)
    /                               \
   /                                 \
P3 (Thread)------S3 (Resource)------P3 (Thread)
```

Following the rules:
- P0's left spoon is S0 and right spoon is S4.
- P1's left spoon is S1 and right spoon is S0.
- P2's left spoon is S2 and right spoon is S1.
- P3's left spoon is S3 and right spoon is S2.
- P4's left spoon is S4 and right spoon is S3.

## Deadlock

In the classic Dining Philosophers problem, the deadlock situation arises when each philosopher picks up their left spoon (or fork) simultaneously. Since every philosopher is holding their left spoon and waiting indefinitely for their right spoon to become available (which won't happen because it's held as the left spoon of the next philosopher), they are in a state of deadlock.

To explain in detail:

1. Philosopher 0 picks up Spoon 0 (to his left).
2. Philosopher 1 picks up Spoon 1 (to his left).
3. Philosopher 2 picks up Spoon 2 (to his left).
4. Philosopher 3 picks up Spoon 3 (to his left).
5. Philosopher 4 picks up Spoon 4 (to his left).

Now, each philosopher is waiting for the spoon to his right. But since all the philosophers picked up the left spoon at the same time, the right spoon for each philosopher is the left spoon for another philosopher. Hence, none of the philosophers will ever pick up the right spoon, and all will wait indefinitely. This situation is a deadlock.

To prevent this deadlock, various solutions can be proposed. A common solution is to ensure that not all philosophers can pick up their left spoon at the same time or introduce an order in which spoons are picked up. Another approach might be to use an arbitrator or a waiter to control access to the spoons.


### `phil_eat`
**Purpose:** Defines the act of a philosopher eating using spoons.

**Logic:** Before a philosopher eats, the function ensures that:
1. Both the spoons are associated with the correct philosopher.
2. Both the spoons are currently in use.
Once the checks pass, it prints out the details of the philosopher and the spoons they're using, increments their `eat_count`, and simulates eating with a sleep function.

### `philosopher_release_both_spoons`
**Purpose:** Releases the spoons after the philosopher finishes eating.

**Logic:** After a philosopher has finished eating:
1. Locks are acquired on both the spoons.
2. It's verified that the spoons are associated with the current philosopher and are in use.
3. Both the spoons are released, and any waiting philosopher is signaled.
4. Locks on the spoons are then released.

### `philosopher_get_access_both_spoons`
**Purpose:** Helps a philosopher acquire both spoons before eating.

**Logic:** 
1. The philosopher tries to acquire the left spoon.
2. If the left spoon is being used by another philosopher, the current philosopher waits.
3. After acquiring the left spoon, the philosopher tries to acquire the right spoon.
4. If the right spoon is available, it's acquired. If not, the philosopher releases the left spoon and waits again.
5. This mechanism prevents deadlocks by ensuring a philosopher does not indefinitely hold onto a single spoon, blocking others.

### `philosopher_fn`
**Purpose:** The main function of each philosopher thread.

**Logic:** The philosopher, in an infinite loop, tries to:
1. Acquire both spoons.
2. If successful, they eat.
3. After eating, they release both spoons.
4. They think (simulated with a sleep function) and then repeat the process.

### `main`
**Purpose:** The main driver function.

**Logic:** 
1. Initializes all spoons.
2. Initializes all philosophers and creates threads for each one.
3. Waits for all philosopher threads to finish (though in this implementation, they loop indefinitely).

## Conclusion
This implementation of the Dining Philosophers problem provides a deadlock-free and race-condition-free solution using mutex locks and condition variables. Proper synchronization ensures that each philosopher gets a chance to eat while maintaining the integrity of the program.

---

## How it solves the problem 

The approach detailed above attempts to solve the Dining Philosophers problem by ensuring that philosophers follow a specific protocol to acquire and release resources (spoons) and by using locks and signals to manage concurrency. Here's a breakdown of how this approach addresses common pitfalls:

1. **Avoid Deadlock**: Deadlock happens when every philosopher picks up the left spoon simultaneously, and they all wait indefinitely for the right spoon. In the `philosopher_get_access_both_spoons` function, after a philosopher acquires the left spoon, they try to acquire the right spoon. If they can't acquire the right spoon, they release the left spoon and wait. This ensures that a philosopher does not keep holding onto one spoon indefinitely, thereby preventing deadlock.

2. **Locks to Ensure Mutual Exclusion**: By using locks on spoons, the approach ensures that no two philosophers can access the same spoon simultaneously. Locks help in establishing mutual exclusion, and preventing race conditions.

3. **Condition Variables or Signals to Coordinate**: When a philosopher cannot acquire a spoon, they wait. Once a philosopher finishes eating and releases the spoons, waiting philosophers are signaled. This mechanism ensures synchronization between philosophers, allowing them to efficiently wait and be notified when resources are available.

4. **Order of Acquiring Resources**: The philosophers try to acquire the left spoon first, then the right. This introduces a standardized sequence which helps in avoiding circular wait conditions.

5. **Resource Release and Wait**: After eating, a philosopher releases both spoons, making them available to others. The philosopher then "thinks" (using a sleep function) before trying to eat again. This wait-time ensures that after releasing the spoons, there's a delay before the same philosopher tries to acquire them again, giving other philosophers a chance to get the spoons.

6. **Consistent Checks**: Before a philosopher eats or releases the spoons, the system checks to ensure that the spoons are correctly associated with the philosopher and are indeed in use. This ensures data integrity and further prevents potential synchronization errors.

By introducing these constraints and mechanisms, the approach prevents the classic pitfalls associated with the Dining Philosophers problem. Philosophers can operate in parallel, making the most efficient use of the available resources without getting into a deadlock or facing contention issues.

---

## Sample Output 

![](./Screenshot%20from%202023-09-08%2000-38-52.png)


## 📚 Resources

The  further reading materials related to the problem statement can be found in the resources section.

---

## 🙌 Contributing

Feel free to fork this project and submit PRs for any improvements or additional features. If you encounter any issues or have questions, please open an issue.

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🤝 Acknowledgements

- A huge shoutout to all those Computer Science enthusiasts who've kept such classic problems alive, fueling countless enlightening discussions.

---

Happy coding, and may you dine without deadlocks!

--- 
