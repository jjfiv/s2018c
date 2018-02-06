#include <stdio.h>
#include <math.h>

// C doesn't come with PI!?!
#define PI 3.14159265358979323846

// We estimate the integral under sin(x) with this many steps. Turn down for
// more speed, up for more accuracy.
#define N 10000

int main(void) {
  double xlim = 2*PI;
  double sum = 0.0;
  for (int i=0; i<N; i++) {
    double t = (i / (double) N) * xlim;
    sum += sin(t);
  }

  // Did you know? C will join together strings separated by spaces. This lets
  // you use less horizontal space in your programs by breaking them into
  // newlines. Unlike Java, you don't use a plus between the pieces of a
  // string, just any kind of space.
  printf("The integral of sin(x) from x=0 to x=2*pi "
      "is approximately %f\n", sum);

  return 0;
}

