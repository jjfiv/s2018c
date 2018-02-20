#ifndef __GAME_H
#define __GAME_H

#include "maze.h"

typedef struct Game_s {
    // A pointer to the maze we're playing.
    Maze* maze;
    // The current player location.
    Point player;
    // The current player score.
    int score;
    // Displaying help screen?
    bool help;
    // Moved from maze.
    Point* rewards;
    // Taken from maze as well, so we can move it around.
    Point* monsters;
} Game;

// Initialize the game with a maze.
void game_init(Game *g, Maze *m);
void game_free(Game *g);
// Display the game via ncurses.
void game_display(Game *g, Point *offset, int anim);

void game_help_display(int anim);
void game_handle_key(Game *g, int key);
void game_update(Game *g);
bool game_player_can_move(Game *g, int x, int y);
bool game_monster_can_move(Game *g, int x, int y);

#endif