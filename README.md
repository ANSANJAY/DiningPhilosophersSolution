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

### `phil_eat`
**Purpose:** Defines the act of a philosopher eating using the spoons.

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
**Purpose:** The main function for each philosopher thread.

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


## 💡 Key Insights

- Mastering thread synchronization is akin to mastering math; practice is crucial.
- A well-structured plan of data structures and program architecture is fundamental to address this problem.

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
