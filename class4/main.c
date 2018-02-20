#include <stdio.h>
#include <string.h> // memset
#include "maze.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./program.exe maze.txt\n");
    return -1;
  }

  // Create a "Maze" on the stack, clear it's values, and then load from a file.
  Maze maze;
  memset(&maze, 0, sizeof(Maze));
  maze_init(&maze, argv[1]);

  printf("Loaded maze:\n");
  maze_print(&maze);


  // clean-up Maze memory before we're done.
  maze_free(&maze);
  return 0;
}
