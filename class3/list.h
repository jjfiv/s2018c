#ifndef __LIST_H
#define __LIST_H

#include <stdbool.h>
#include <stdio.h>

// Our "pointer" type, which refers to the next thing in a list, is defined to be an int here.
typedef int POINTER;
// Our "value" type, or what we're putting in our lists, is defined to be a double here.
typedef double VALUE;

// An entry in the pool contains a "pointer" to the next element and a value.
struct Entry {
  // We assume it's part of a list; if not, it's next will be NULL_ENTRY.
  POINTER next;
  // The value stored. We never clear these, but set them anew when we allocate an entry from the pool.
  VALUE value;
};

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
// This function demonstrates writing one of our lists to a particular file.
void fprint_list(FILE* f, POINTER start);
// This function demonstrates writing one of our lists to the console.
void print_list(POINTER start);
// This is a method to debug and visualize the lists/data in the pool.
void debug_pool(void);

#endif

