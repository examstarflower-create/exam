# Lab 0: Linked list in C Programming

## This is sample lab for practice and isn't part of your grade

This sample lab is intended to help you become familiar with the low-level semantics of the C programming language that you will be using throughout this course, as well as with our GitLab submission system.
Although this lab is not mandatory, we strongly recommend practicing it in advance.

## Fork & Clone instructions

Please refer to our guide on how to fork and clone from GitLab (https://piazza.com/class/meuz7dsu4ap3mb/post/13).

**Make sure you fork the repository to your private namespace!**


## 1. Introduction

For this lab, your task is to fill in the skeleton code and implement the doubly linked list. You must only fill in the skeleton code in the`list.c` file. You may modify the `test.c` file and add the `iterate_print_keys()` function to help with your debugging, however you must make sure your tests work with the original `test.c ` file.

## 2. Doubly Linked List

For this lab, you will need to implement a doubly linked list, where there are two nodes, `head` and the `tail` node that are reference nodes. They do not hold any meaningful `key` values, just `-1` as a key. The `head` and `tail` , nodes represent the beginning and the end of the list. Also the invariant of the `head` and `tail` node is that, the `tail`'s next node is the `head`, and the `head`'s previous node is the `tail`. This provides the advantage of being able to find the `tail` of the list, when given the `head`, with ease. Once you have the `head` and the `tail`, you can set your iteration to begin at the head, and end at the tail.

The functions that need to be implemented are provided in the `list.c` file. The requirements of each skeleton function is described in the block comment above the skeleton function.

## 3. Memory Management

You will need to dynamically allocate memory for new nodes using the `malloc()` function, and free any deleted nodes using the `free()` function.
You can access the reference for the two functions using the following commands:

```sh
$ man malloc
$ man free
```

## 4. Test cases must be met

All the test cases implemented in the `test.c` file must be met. As of this writing, there are eight test cases. Make sure to satisfy all of the test cases. You can test your `list.c` implementation using the following command

```sh
$ make test
```

There are three test failures that have been identified (there may be more).
1. Segmentation Fault: there is a pointer dereference in your code that is to an incorrect memory address!
2. Test Failure: some of the test cases are not being satisfied.
3. Timeout: your code is not finishing up in time. Perhaps you have a infinite loop in your code?

Once you fix all the problems, and your `make test` results in a `Passed the test, Everything worked!` output, then you should be ready to hand in your lab. Make sure your tests pass with the original `test.c` file.

## 5. Hand in Instructions

Please refer to our guide on how to submit your work to GitLab (https://piazza.com/class/meuz7dsu4ap3mb/post/13)

Every semester, many students make mistakes during the submission process and end up at a disadvantage. To avoid this, be sure to practice in advance using the sample lab.

