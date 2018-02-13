#include <assert.h>
#include "list.h"

// We've not dealt with command line arguments yet.
// Try running this program without arguments to see the asserts fail:
//   gcc pool_list.c && ./a.out
// Try running it with my data file:
//   gcc pool_list.c && ./a.out test.txt
int main(int argc, char **argv) {
  clear_pool();

  // Check to make sure arguments are provided with assert statements.
  assert(argv != NULL);
  assert(argc == 2);

  FILE* input = fopen(argv[1], "r");
  assert(input != NULL);

  // Create a list of [9,8,7]
  POINTER test_list = push_front(9.0, push_front(8.0, alloc(7.0)));
  
  // Print test_list.
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Create a pointer to hold a list from our file.
  POINTER file_list = NULL_ENTRY;

  // Load up entries from a file.
  while (true) {
    double value;
    // Read a floating point value from the input file.
    int status = fscanf(input, "%lf", &value);
    if (status == EOF) break;
    if (status != 1) {
      // Be nice about errors and quit if we get the wrong file.
      fprintf(stderr, "Unable to read a value, fscanf -> %d", status);
      return -1;
    }

    // Add the value we read into the list.
    file_list = push_front(value, file_list);
  }

  // Make sure we read the things we wanted to read.
  printf("File List:\t");
  fprint_list(stdout, file_list);
  
  // Print test_list; show that it still works -- reading from the file should not have changed this!
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Look at the pool.
  debug_pool();


  // Now test the functions we wrote:
  assert(list_size(test_list) == 3);

  // Add an item, check that size increases:
  push_back(test_list, 1.0);
  assert(list_size(test_list) == 4);

  // Now make sure the list is actually correct.
  double expected[] = {9,8,7,1};
  assert(list_equals_array(test_list, expected, 4));

  return 0;
}
