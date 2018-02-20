#include "point.h"
#include <assert.h>

void point_init(Point *p, int x, int y) {
    p->x = x;
    p->y = y;
    p->next = NULL;
}

int point_count(Point *p) {
    if (p == NULL) return 0;
    return 1 + point_count(p->next);
}

bool has_point(Point *p, int x, int y) {
    if (p->x == x && p->y == y) {
        return true;
    }
    if (p->next != NULL) {
        return has_point(p->next, x, y);
    }
    return false;
}

Point* alloc_point(int x, int y) {
    Point* p = malloc(sizeof(Point));
    assert(p != NULL);
    point_init(p, x, y);
    return p;
}

void points_free(Point *list) {
    if (list == NULL) return;
    Point *next = list->next;
    free(list);
    points_free(next);
}

void push_point(Point **list, int x, int y) {
    Point* p = alloc_point(x, y);
    p->next = *list;
    *list = p;
}