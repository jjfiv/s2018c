#include "game.h"

#include <assert.h>
#include <ncurses.h>

void game_init(Game *g, Maze *m) {
    assert(g != NULL);
    assert(m != NULL);
    g->maze = m;
    point_init(&g->player, m->start.x, m->start.y);
    g->score = 0;
    g->help = false;
    g->rewards = m->rewards;
    m->rewards = NULL;
}

void game_display(Game *g, Point *offset, int anim) {
  assert(g != NULL);
  Maze *m = g->maze;
  assert(m != NULL);
  assert(m->data != NULL);

  int left = offset->x;
  int top = offset->y;
  int w = m->size.x;
  int h = m->size.y;

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      move(top+y,left+x);
      int cell = x + y*w;
      addch(m->data[cell]);
    }
  }

  for (Point *p = g->rewards; p != NULL; p = p->next) {
    move(top + p->y, left + p->x);
    if ((anim / 10) % 2 == 0) {
        attron(COLOR_PAIR(1));
        addch('*');
        attroff(COLOR_PAIR(1));
    } else {
        attron(COLOR_PAIR(2));
        addch('*');
        attroff(COLOR_PAIR(2));
    }
  }

  move(top + g->player.y, left + g->player.x);
  attron(COLOR_PAIR(3));
  addch('@');
  attroff(COLOR_PAIR(3));
}

void game_help_display() {
    mvprintw(0,0,"Press 'h' to return to game, and 'q' to quit.");
    mvprintw(1,2,"Press 'w' to move up.");
    mvprintw(2,2,"Press 's' to move down.");
    mvprintw(3,2,"Press 'd' to move right.");
    mvprintw(4,2,"Press 'a' to move left.");
}

void game_handle_key(Game *g, int key) {
    Point dir;
    point_init(&dir, 0, 0);
    if (key == KEY_UP || key == 'w') {
        dir.y = -1;
    } else if (key == KEY_LEFT || key == 'a') {
        dir.x = -1;
    } else if (key == KEY_RIGHT || key == 'd') {
        dir.x = +1;
    } else if (key == KEY_DOWN || key == 's') {
        dir.y = +1;
    }

    if (game_can_move(g, g->player.x + dir.x, g->player.y + dir.y)) {
      g->player.x += dir.x;
      g->player.y += dir.y;
    }
}

bool game_can_move(Game *g, int x, int y) {
    // TODO: upgrade this.
    return true;
}

void game_update(Game *g) {
    int px = g->player.x;
    int py = g->player.y;

    // TODO if player is on top of a reward, take it out of the list and increase score.
}
