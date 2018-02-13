#ifndef __POOL_LIST_H
#define __POOL_LIST_H 1

#include <stdbool.h>
#include <stdio.h>

// A pool is a data structure often seen in C programming and resource-constrained systems. You want to have variable length "linked" lists, but you want to bound how big they can possibly be as a group, and you want to be able to make a new node in a linked list very quickly.

// There are 8 or 2^3 items in our pool by default.
// People tend to pick powers of 2 for things like this because they're faster on a computer. 
#define POOL_SIZE (8)

// This is a magic pointer that signifies there is no "next" when we see it.
#define NULL_ENTRY (-1)

// Our "pointer" type, which refers to the next thing in a list, is defined to be an int here.
typedef int POINTER;
// Our "value" type, or what we're putting in our lists, is defined to be a double here.
typedef double VALUE;

// An entry in the pool contains a "pointer" to the next element and a value.
struct Entry {
  // This tells us whether this entry is in use or not.
  bool available;
  // This points to the next item in the list.
  POINTER next;
  // The value stored. We never clear these, but set them anew when we allocate an entry from the pool.
  VALUE value;
};

// Set up the pool to be a set of free entries so that we can grab one later.
void clear_pool(void);

// This function creates a new List Entry and returns a POINTER to it.
POINTER alloc(VALUE value);
// Calculate the length of a linked list starting at start.
int list_size(POINTER start);
// Add a new entry to the front of 'list' with 'value'.
POINTER push_front(VALUE value, POINTER list);
// Add a new entry containing 'value' to the end of the list starting with 'start'.
void push_back(POINTER start, VALUE value);
// Given a list and an array[array_len], return true if they have the same values in the same order.
bool list_equals_array(POINTER list, double* array, int array_len);
// Given a list, take its first element off and 'free' it.
POINTER free_front(POINTER list);
// Given a list, free all of its items.
void free_list(POINTER list);

// This function demonstrates writing one of our lists to a particular file.
void fprint_list(FILE* f, POINTER start);
// This function demonstrates writing one of our lists to the console.
void print_list(POINTER start);
// This is a method to debug and visualize the lists/data in the pool.
void debug_pool(void);

#endif

