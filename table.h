#pragma once

#include "vector.h"
#include "object.h"
#include "wall.h"

struct table {
    struct object_trans trans;
    struct wall *walls;
    size_t walls_num;
};

extern void(*on_hole_event)(struct wall *w, struct ball *b);

void init_default_table(struct table *table);
void draw_table(const struct table *table);
