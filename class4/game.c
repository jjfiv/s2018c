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
    g->monsters = m->monster_starts;
    m->monster_starts = NULL;
}

void game_free(Game *g) {
    points_free(g->rewards);
    points_free(g->monsters);
    g->rewards = NULL;
    g->monsters = NULL;
}

void game_display(Game *g, Point *offset, int anim) {
  assert(g != NULL);
  assert(g->maze != NULL);
  assert(g->maze->data != NULL);

  int left = offset->x;
  int top = offset->y;
  int w = g->maze->size.x;
  int h = g->maze->size.y;

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      move(top+y,left+x);
      int cell = x + y*w;
      addch(maze_get(g->maze, x, y));
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

  for (Point *m = g->monsters; m != NULL; m = m->next) {
      move(top + m->y, left + m->x);
      attron(COLOR_PAIR(4));
      addch('m');
      attroff(COLOR_PAIR(4));
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
    if (key == 'w') {
        dir.y = -1;
    } else if (key == 'a') {
        dir.x = -1;
    } else if (key == 'd') {
        dir.x = +1;
    } else if (key == 's') {
        dir.y = +1;
    }

    // Move player, if allowed:
    if (game_player_can_move(g, g->player.x + dir.x, g->player.y + dir.y)) {
      g->player.x += dir.x;
      g->player.y += dir.y;
    }
}

static bool maze_is_in_bounds(Maze *m, int x, int y) {
    // check to ensure we're within the map bounds:
    if (x < 0 || y < 0)
        return false;
    if (x >= m->size.x || y >= m->size.y)
        return false;
    return true;
}

bool game_player_can_move(Game *g, int x, int y) {
    assert(g != NULL);
    assert(g->maze != NULL);
    if (!maze_is_in_bounds(g->maze, x, y)) {
      return false;
    }

    // TODO: upgrade this.
    // Right now the player can walk through walls (cheating).
    // Right now the player can walk through monsters (also cheating).
    return true;
}
bool game_monster_can_move(Game *g, int x, int y) {
    assert(g != NULL);
    assert(g->maze != NULL);

    // 1. Monster cannot move out of bounds.
    if (!maze_is_in_bounds(g->maze, x, y)) {
      return false;
    }

    // 2. Monster cannot go through doors or walls.
    char dest = maze_get(g->maze, x, y);
    if (dest == '.' || dest == '#') {
        return false;
    }

    // 3. Monster cannot step on top of a player.
    if (g->player.x == x && g->player.y == y) {
        return false;
    }
    
    // 4. Monster cannot step on top of a reward thingy.
    if (has_point(g->rewards, x, y)) {
        return false;
    }

    // Otherwise, ok.
    return true;
}

void random_dir(Point *p) {
  switch (rand() % 4) {
  case 0:
    p->x = -1;
    break;
  case 1:
    p->x = 1;
    break;
  case 2:
    p->y = 1;
    break;
  case 3:
    p->y = -1;
    break;
  }
}

void game_update(Game *g) {
  int px = g->player.x;
  int py = g->player.y;

  // Move all monsters: (if allowed)
  int i =0;
  for (Point *m = g->monsters; m != NULL; m = m->next, i++) {
    Point dir;
    point_init(&dir, 0, 0);
    random_dir(&dir);
    if (game_monster_can_move(g, m->x + dir.x, m->y + dir.y)) {
        m->x += dir.x;
        m->y += dir.y;
    }
  }

  // TODO if player is on top of a reward: 
  //  - take it out of the list 
  //  - increase score.
}
