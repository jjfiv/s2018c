#include <assert.h>
#include "list.h"

// A pool is a data structure often seen in C programming and resource-constrained systems. You want to have variable length "linked" lists, but you want to bound how big they can possibly be as a group, and you want to be able to make a new node in a linked list very quickly.

// There are 32 or 2^5 items in our pool by default.
// People tend to pick powers of 2 for things like this because they're faster on a computer. 
#define POOL_SIZE (32)
// A more reasonable size might be 4096, or 2^12.
//#define POOL_SIZE (1 << 12)

// This is a magic pointer that signifies there is no "next" when we see it.
#define NULL_ENTRY (POOL_SIZE+1)


// In C, "static" means "private to this file" and is sometimes required for constants -- it can also help the compiler optimize.
static struct Entry pool[POOL_SIZE];
// This POINTER is the start of a list, actually. This linked list will have all the items in the pool that are "free" or not currently used.
static POINTER free = 0;

// We need to make sure that the pool starts in a reasonable state.
// Therefore, we make the free list point at the first item in the pool, and every item in the pool point to the next except the last, which has the magical end of list marker, NULL_ENTRY.
void clear_pool(void) {
  free = 0;
  for (int i=0; i<POOL_SIZE; i++) {
    pool[i].next = i+1;
    pool[i].value = -42;
  }
  pool[POOL_SIZE-1].next = NULL_ENTRY;
}

// This function takes a value, puts it in an Entry, and returns a pointer to that Entry (its index) to us.
POINTER alloc(VALUE value) {
  // Pop from the "free" list.
  POINTER step = free;
  // If there's more free nodes, then make sure we know where they are.
  if (step != NULL_ENTRY) {
    // The second entry in the free list is now the first entry.
    free = pool[step].next;
  }
  // The entry that was previously free is now a list of length 1.
  pool[step].next = NULL_ENTRY;
  pool[step].value = value;
  // Pass back the location of that entry.
  return step;
}

// How do you count the items in a linked list?
int list_size(POINTER start) {
  // TODO, does nothing right now.
  return -1;
}

// How do you add an item to the end of a linked list?
void push_back(POINTER start, VALUE value) {
  // TODO, does nothing right now.
  return;
}

bool list_equals_array(POINTER list, double* array, int array_len) {
  if (list_size(list) != array_len) return false;
  // TODO, do this better!
  return false;
}

// Given a value and a list, alloc a new entry and put it on the front of this list.
POINTER push_front(VALUE value, POINTER list) {
  POINTER new = alloc(value);
  assert(new != NULL_ENTRY);
  // To push on the front of a linked list, we take our new node and set it's next pointer to be the old beginning of the list.
  pool[new].next = list;
  return new;
}

// Given a list, take its first element off and put it in the free list.
POINTER free_front(POINTER list) {
  // Don't do anything with empty lists.
  assert(list != NULL_ENTRY);

  // What is leftover of this list once we chop the first one off?
  POINTER leftover = pool[list].next;
  
  // Move our first node into the "free" list.
  pool[list].next = free;
  free = list;

  // return the rest of this linked list.
  return leftover;
}

// This function demonstrates writing one of our linked lists to a particular file.
void fprint_list(FILE* f, POINTER start) {
  for(POINTER x = start; x != NULL_ENTRY; x = pool[x].next) {
    fprintf(f, "%1.3f ", pool[x].value);
  }
  fprintf(f, "\n");
}
// This is the difference between printf and fprintf:
void print_list(POINTER start) {
  fprint_list(stdout, start);
}

// This is a method to debug and visualize the lists/data in the pool.
void debug_pool(void) {
  printf("free_list_start = %d\n", free);
  printf("NULL_ENTRY (end of list) = %d\n", NULL_ENTRY);
  for (int i=0; i<POOL_SIZE; i++) {
    printf("pool[%d] {.next=%d, .value=%lf}\n", i, pool[i].next, pool[i].value);
  }
}

