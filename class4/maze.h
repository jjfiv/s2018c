#ifndef __MAZE_H
#define __MAZE_H

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point size;
  Point start;
  char* data;
} Maze;

void maze_init(Maze* m, const char* file);
void maze_print(Maze* m);
void maze_free(Maze *m);

#endif
