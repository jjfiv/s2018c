#include <assert.h>
#include <stdlib.h>
#include "pool_list.h"

// In C, "static" means "private to this file" and is sometimes required for
// constants -- it can also help the compiler optimize.
static struct Entry pool[POOL_SIZE];

// We need to make sure that the pool starts in a reasonable state.
//
// Therefore, we make the free list point at the first item in the pool, and
// every item in the pool point to the next except the last, which has the
// magical end of list marker, NULL_ENTRY.
void clear_pool(void) {
  for (int i=0; i<POOL_SIZE; i++) {
    pool[i].available = true;
    pool[i].next = NULL_ENTRY;
    pool[i].value = -42;
  }
}

// This function takes a value, puts it in an Entry, and returns a pointer to
// that Entry (its index) to us.
POINTER alloc(VALUE value) {
  // Find the first entry in the pool that is "free".
  int found = -1;
  for (int i=0; i<POOL_SIZE; i++) {
    // if this one is available, save its location and break.
    if (pool[i].available) {
      found = i;
      break;
    }
  }
  // if we get here, and found is still -1, then we are out of free entries! Let's crash.
  if (found < 0) {
    fprintf(stderr, "Ran out of memory!\n");
    debug_pool();
    exit(-1);
  }

  // Mark this one as used, put the value inside, and make it the "end" of its list.
  pool[found].available = false;
  pool[found].next = NULL_ENTRY;
  pool[found].value = value;
  return found;
}

// How do you count the items in a linked list?
int list_size(POINTER start) {
  // This is the easiest. Consider the implementation of fprint_list if stuck.
  return 42;
}

// How do you add an item to the end of a linked list?
void push_back(POINTER start, VALUE value) {
  // TODO: this is harder than list_size.
}

bool list_equals_array(POINTER list, double* array, int array_len) {
  if (list_size(list) != array_len) return false;

  // This one is hard too. Need to loop through array[i] and list at the same time.
  return true; // currently a lie.
}

// Given a value and a list, alloc a new entry and put it on the front of this list.
POINTER push_front(VALUE value, POINTER list) {
  POINTER new = alloc(value);
  assert(new != NULL_ENTRY);
  // To push on the front of a linked list, we take our new node and set it's
  // next pointer to be the old beginning of the list.
  pool[new].next = list;
  return new;
}

// Given a list, take its first element off and put it in the free list.
POINTER free_front(POINTER list) {
  // Don't do anything with empty lists.
  assert(list != NULL_ENTRY);

  // What is leftover of this list once we chop the first one off?
  POINTER leftover = pool[list].next;
  
  // Mark this element as "free".
  pool[list].available = true;

  // return the rest of this linked list.
  return leftover;
}

void free_list(POINTER list) {
  POINTER rest = free_front(list);
  if (rest == NULL_ENTRY) {
    return;
  }
  // Recursion?!?!
  free_list(rest);
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

// C doesn't know how to print booleans, so we need to do it ourselves.
static const char TRUE[] = "true";
static const char FALSE[] = "false";

// Get a string based on a boolean value.
static const char* str_of_bool(bool val) {
  if (val) return TRUE;
  return FALSE;
}

// This is a method to debug and visualize the lists/data in the pool.
void debug_pool(void) {
  printf("NULL_ENTRY (end of list) = %d\n", NULL_ENTRY);
  for (int i=0; i<POOL_SIZE; i++) {
    printf("pool[%d] {.available=%s, .next=%d, .value=%lf}\n", 
        i, str_of_bool(pool[i].available), pool[i].next, pool[i].value);
  }
}

