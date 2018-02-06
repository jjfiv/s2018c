#include <stdio.h>

// Fizz-Buzz is a famous interview problem.
// We will do it to learn how to write a text file in C.
//
//
// Print the numbers from 0 to 100 (inclusive) to the file "fizzbuzz.txt" EXCEPT:
//  - If the number is divisible by 3, print "Fizz".
//  - If the number is divisible by 5, print "Buzz".
//  - If the number is divisible by both, print "FizzBuzz".
// Do not output blank lines.
//
int main(void) {
  // Never hard-code numbers if you can help it.
  const int N = 100;

  // Open a file for writing.
  FILE* out = fopen("fizzbuzz.txt", "w");

  // The first argument to fprintf is the file to write to.
  // The second argument is your formatting 'pattern'
  // The rest of the arguments are what goes into your pattern.
  fprintf(out, "This is the value of N=%d\n", N);
  
  // A pattern *can* be a regular string without any %-patterns.
  // In this case, we only need two arguments.
  fprintf(out, "This doesn't work yet!\n");

  // We need to close the file we're writing to, otherwise we may lose data!
  fclose(out);

  // Tell the shell/terminal that we were successful.
  return 0;
}
