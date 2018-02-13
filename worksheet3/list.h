#ifndef __LIST_H
#define __LIST_H 1

#include <stdbool.h>
#include <stdio.h>

// Our "value" type, or what we're putting in our lists, is defined to be a double here.
typedef double VALUE;

// An entry in the pool contains a "pointer" to the next element and a value.
typedef struct Entry_s {
  // We assume it's part of a list; if not, it's next will be NULL_ENTRY.
  struct Entry_s* next;
  // The value stored. We never clear these, but set them anew when we allocate an entry from the pool.
  VALUE value;
} Entry;


// This function creates a new List Entry and returns a Entry* to it.
Entry* alloc(VALUE value);
// Calculate the length of a linked list starting at start.
int list_size(Entry* start);
// Add a new entry to the front of 'list' with 'value'.
Entry* push_front(VALUE value, Entry* list);
// Add a new entry containing 'value' to the end of the list starting with 'start'.
void push_back(Entry* start, VALUE value);
// Given a list and an array[array_len], return true if they have the same values in the same order.
bool list_equals_array(Entry* list, double* array, int array_len);
// Given a list, take its first element off and 'free' it.
Entry* free_front(Entry* list);
// Given a list, releases all the memory.
void free_list(Entry* list);
// This function demonstrates writing one of our lists to a particular file.
void fprint_list(FILE* f, Entry* start);
// This function demonstrates writing one of our lists to the console.
void print_list(Entry* start);

#endif

