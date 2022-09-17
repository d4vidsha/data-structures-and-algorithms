# COMP20003: Algorithms and Data Structures
A subject from the University of Melbourne. This repository contains code relating to the workshops for this subject. The answers are not guaranteed to be the best solution, but they are the best I could come up with at the time. There are some good algorithms in here and are notably listed below. See the [subject outline](https://handbook.unimelb.edu.au/2022/subjects/comp20003) for more information on the subject.

---
### Folders
- `ass1` contains an implementation of quicksort on linked lists as well as a binary search algorithm.

- `ass2` contains an implementation of quicksort on arrays (which are more efficient than on linked lists due to arrays having its random access quality) as well as an implementation of a quadtree data structure, which is a data structure that is used to store points in a 2D space. Searching for a point in a quadtree is done in O(log n) time, which is much faster than say searching for a point in a linked list, which is O(n) time.

- `W8.3` contains an implementation of mergesort and queues. There is also a program that takes in a random number which represents the number of elements in an array. The program then generates a linked list with random numbers and sorts it using the mergesort algorithm. The program then prints out the sorted linked list. Mergesort is done bottom-up (storing the sorted sublists in a queue before merging as opposed to top-down/recursive merging) and the linked list is sorted in ascending order. There is another implementation of a queue in `W5.2` which may be more efficient than the one in `W8.3`.