#include "maze.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int lhs, int rhs) { return (lhs > rhs) ? lhs : rhs; }

void maze_init(Maze *out, const char *file) {
  assert(out != NULL);

  FILE *fp = fopen(file, "r");

  // First, calculate the size of the file we're loading.
  int max_w = 0;
  int w = 0;
  int h = 0;
  while (true) {
    int next = fgetc(fp);
    if (next == EOF) {
      max_w = max(w, max_w);
      break;
    } else if (next == '\n') {
      h++;
      max_w = max(w, max_w);
      w = 0;
    } else {
      w++;
    }
  }

  int size = max_w * h;
  printf("File Dimensions: %dx%d=%d\n", max_w, h, size);

  out->size.x = max_w;
  out->size.y = h;
  out->start.x = -1;
  out->start.y = -1;
  out->data = (char *)malloc(size);
  assert(out->data != NULL);

  // Clear the data we've just asked for..
  memset(out->data, 0, size);

  // Go back to the beginning of the file.
  fseek(fp, 0, SEEK_SET);

  // Load the data in, now that we have some memory of the right size.
  w = 0;
  h = 0;
  while (true) {
    int next = fgetc(fp);
    if (next == EOF)
      break;
    else if (next == '\n') {
      h++;
      w = 0;
    } else {
      char tile = (char) next;
      // If we get to the "person" marker, set the tile to be blank.
      if (next == '@') {
        out->start.x = w;
        out->start.y = h;
        tile = ' ';
      }
      int cell = h * out->size.x + w;
      printf("%d,%d,%d: %c\n",w,h,cell,next);
      out->data[cell] = tile;
      w++;
    }
  }

  fclose(fp);
}

void maze_free(Maze *m) {
  free(m->data);
  m->data = NULL;
}

void maze_print(Maze* m) {
  assert(m != NULL);
  assert(m->data != NULL);
  int w = m->size.x;
  int h = m->size.y;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int cell = x + y*w;
      printf("%c", m->data[cell]);
    }
    printf("\n");
  }
}