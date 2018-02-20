#ifndef __MAZE_H
#define __MAZE_H

#include "point.h"

typedef struct {
  // A point containing the size of the map.
  Point size;
  // A point containing the start position of the character ('@').
  Point start;
  // A list of points containing the rewards ('*').
  Point* rewards;
  // A list of points where monsters start ('m');
  Point* monster_starts;
  // A "2d" array that represents the walls and floors of the map.
  char* data;
} Maze;

void maze_init(Maze* m, const char* file);
void maze_print(Maze* m);
void maze_free(Maze *m);
char maze_get(Maze *m, int x, int y);


#endif
