# DiningPhilosophersSolution
An implementation of the Dining Philosophers problem, focusing on concurrency control via mutexes and semaphores. This repo demonstrates how to manage multiple processes accessing shared resources, aiming to solve issues of deadlock and contention. Includes code examples and a guide.




---

# 🍽️ Dining Philosopher Problem 

This repository delves into one of the classic synchronization problems in Computer Science - The Dining Philosopher Problem. 

![](https://github.com/ANSANJAY/DiningPhilosophersSolution/blob/main/An_illustration_of_the_dining_philosophers_problem.png)

## 📌 Table of Contents

- [Introduction](#introduction)
- [Diagram Description](#diagram-description)
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

## 💡 Key Insights

- Mastering thread synchronization is akin to mastering math; practice is crucial.
- A well-structured plan of data structures and program architecture is fundamental to address this problem.


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
