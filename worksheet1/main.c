#include "operations.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  // Test addition.
  assert(4 == addition(2,2));
  assert(14 == addition(12,2));
  assert(4 == addition(6,-2));
  assert(10 == addition(-5,15));
  assert(4 == addition(1,3));
  assert(4 == addition(3,1));
  
  // Test subtraction.
  assert(0 == subtraction(2,2));
  assert(10 == subtraction(12,2));
  assert(8 == subtraction(6,-2));
  assert(-20 == subtraction(-5,15));
  assert(-2 == subtraction(1,3));
  assert(2 == subtraction(3,1));
  
  // Test multiplication.
  assert(4 == multiplication(2,2));
  assert(24 == multiplication(12,2));
  assert(-12 == multiplication(6,-2));
  assert(-75 == multiplication(-5,15));
  assert(3 == multiplication(1,3));
  assert(3 == multiplication(3,1));
  
  // Test division.
  assert(1 == division(2,2));
  assert(6 == division(12,2));
  assert(-3 == division(6,-2));
  assert(0 == division(-5,15));
  assert(0 == division(1,3));
  assert(3 == division(3,1));

  // Print a status.
  puts("All operations completed successfully.");

  // Tell command line that everything was cool.
  return 0;
}
