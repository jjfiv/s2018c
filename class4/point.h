#ifndef __POINT_H
#define __POINT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Point_s {
  int x;
  int y;
  struct Point_s* next;
} Point;

// Create a point at (x,y) and set its "next" to zero.
void point_init(Point *p, int x, int y);
// Since a point is also a list, this method looks to see if any of the points are equal to the query.
bool has_point(Point *p, int x, int y);

int point_count(Point *p);

// Create a point (x,y) on the heap.
Point* alloc_point(int x, int y);
// Add a point to the front of ``list``.
void push_point(Point **list, int x, int y);
// Free a list of points:
void points_free(Point *list);

#endif