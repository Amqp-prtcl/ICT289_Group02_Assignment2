#pragma once

#include "vector.h"
#include "object.h"
#include "wall.h"

struct table {
    struct object_trans trans;
    struct wall *walls;
    size_t walls_num;
};

void init_default_table(struct table *table);
void draw_table(const struct table *table);
