#include <assert.h>
#include <stdlib.h>
#include "list.h"

// This function takes a value, puts it in an Entry, and returns a pointer to
// that Entry (its index) to us.
Entry* alloc(VALUE value) {
  Entry* p = malloc(sizeof(Entry));
  assert(p != NULL);
  p->value = value;
  p->next = NULL;
  return p;
}

// How do you count the items in a linked list?
int list_size(Entry* start) {
  // This is the easiest. Consider the implementation of fprint_list if stuck.
  return 42;
}

// How do you add an item to the end of a linked list?
void push_back(Entry* start, VALUE value) {
  // TODO: this is harder than list_size.
}

bool list_equals_array(Entry* list, double* array, int array_len) {
  if (list_size(list) != array_len) return false;

  // This one is hard too. Need to loop through array[i] and list at the same time.
  return true; // currently a lie.
}

// Given a value and a list, alloc a new entry and put it on the front of this list.
Entry* push_front(VALUE value, Entry* list) {
  Entry* new = alloc(value);
  assert(new != NULL);
  // To push on the front of a linked list, we take our new node and set it's
  // next pointer to be the old beginning of the list.
  new->next = list;
  return new;
}

// Given a list, take its first element off and put it in the free list.
Entry* free_front(Entry* list) {
  // Don't do anything with empty lists.
  assert(list != NULL);

  // What is leftover of this list once we chop the first one off?
  Entry* leftover = list->next;
  free(list);

  // return the rest of this linked list.
  return leftover;
}

void free_list(Entry* list) {
  Entry* rest = free_front(list);
  if (rest == NULL) {
    return;
  }
  // Recursion?!?!
  free_list(rest);
}

// This function demonstrates writing one of our linked lists to a particular file.
void fprint_list(FILE* f, Entry* start) {
  for(Entry* x = start; x != NULL; x = x->next) {
    fprintf(f, "%1.3f ", x->value);
  }
  fprintf(f, "\n");
}

// This is the difference between printf and fprintf:
void print_list(Entry* start) {
  fprint_list(stdout, start);
}

