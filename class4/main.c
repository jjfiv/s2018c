#define _GNU_SOURCE 1

#include "game.h"
#include <unistd.h> // usleep
#include <ncurses.h>
#include <stdio.h>
#include <string.h> // memset

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
  printf("Start: %d,%d\n", maze.start.x, maze.start.y);
  printf("Rewards: %d\n", point_count(maze.rewards));
  maze_print(&maze);
  
  initscr();
  start_color();
  // rewards alternate between white and yellow.
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  // the player is green.
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  // the monsters are red.
  init_pair(4, COLOR_RED, COLOR_BLACK);
  noecho();
  nocbreak();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  
  Game game;
  game_init(&game, &maze);

  int anim = 0;
  while(true) {
    clear();
    int x, y;
    // This is a "macro" so we don't use pointers.
    getmaxyx(stdscr, y, x);

    Point offset;
    point_init(&offset, 2, 4);

    if (!game.help) {
      game_display(&game, &offset, anim);
      mvprintw(0,0, "Press 'q' to quit and 'h' for help.");
      mvprintw(2,0, "Points: %d", game.score);
    } else {
      game_help_display(anim);
    }

    // draw the screen.
    refresh();
    // keep a counter so that we have some sense of how to animate things.
    anim = (anim + 1) % 1000;

    // Ask for a key.
    int key = getch();
    if (key == ERR) {
      // No key was pressed.
      // 0.05s = 50 ms = 50 * 1000 us
      usleep(50*1000);
      continue;
    } else if (key == 'q') {
      break;
    } else if (key == 'h') {
      game.help = !game.help;
    } else if (!game.help) {
      // Only do game stuff if we're not on the help screen.
      game_handle_key(&game, key);
      // Monsters only move when players do, for now.
      game_update(&game);
    
      // Force a key-press so we can debug...
      // while(getch() == ERR) { }
    }

  }

  endwin();


  // clean-up Maze and Game memory before we're done.
  game_free(&game);
  maze_free(&maze);
  return 0;
}
