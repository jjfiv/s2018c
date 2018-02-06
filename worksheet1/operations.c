#include "operations.h"

// This is a function named "addition" that takes two arguments, "op1" and
// "op2" and returns their sum.
int addition(int op1, int op2) {
  return op1 + op2;
}

// Create a function for subtraction that is named "subtraction", takes two
// ints, and returns the difference. (You should subtract the SECOND number
// from the FIRST)
int subtraction(int op1, int op2) {
  return op1 - op2;
}

// Create a function for multiplication that is named "multiplication", takes
// two ints, and returns the product.
int multiplication(int op1, int op2) {
  return op1 * op2;
}

// Create a function for division that is named "division", takes two ints, and
// returns the quotient. (You should divide the first number by the second
// number. Keep in mind we are using integer division, so all answers will be
// automatically rounded down.)
int division(int op1, int op2) {
  return op1 / op2;
}

int snafucate(int op1) {
  return op1*op1*op1;
}

//NOTE: you cannot test your code until you have created the subtraction,
//multiplication, and division functions (though they do not need to work).

