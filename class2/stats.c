#include <stdio.h>
// This is a constant defined using the "preprocessor".
#define MAX_ENTRIES 5

// Given an array of doubles `entries` of size `length`, let's calculate
// some basic statistics (Check wikipedia if you don't remember how to
// do stddev).
void print_stats(double *entries, int length) {
  double sum = 0;
  double mean = 0;
  double max = 0;
  double min = 0;
  double stddev = 0;
  for (int i=0; i<length; i++) {
    sum += entries[i];
  }
  printf("\tN=%d\n", length);
  printf("\tsum=%lf\n", sum);
  printf("\tmean=%lf\n", mean);
  printf("\tmax=%lf\n", max);
  printf("\tmin=%lf\n", min);
  printf("\tstddev=%lf\n", stddev);
}

// When scanf gets the wrong thing, it halts immediately. This function
// "clears" input by reading until the next newline or the end of the
// stream (EOF).
void ignore_input() {
  int c;
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n')
      break;
  }
}

int main(void) {
  // Keep track of an array of items.
  double entries[MAX_ENTRIES];
  // Keep track of how many items are in it.
  int filled = 0;

  while(1) {
    // "clear" the array by ignoring the old items.
    filled = 0;

    // Stop when we run out of space.
    while(filled < MAX_ENTRIES) {
      // Tell the user what they're writing to.
      printf("entry[%d]=", filled);
      fflush(stdout);

      // Take input if possible.
      double input;
      int status = scanf("%lf", &input);

      if (status == 1) {
        // They entered a number!
        entries[filled++] = input;
        // When we get an item, print the statistics so far.
        print_stats(entries, filled);
      } else if(status == EOF) {
        // They tried to quit.
        printf("Ctrl-D received. Exiting.\n");
        return 0;
      } else {
        // They entered something that's not a number.
        printf("Error. ");
        printf("Enter only a single floating point number (e.g., 3.14).\n");
        ignore_input();
      }
    }

    // TODO: print all the items entered here:
  }
}

