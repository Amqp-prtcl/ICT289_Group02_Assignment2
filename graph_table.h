#pragma once

#include "table_const.h"
#include "vector.h"
#include "object.h"

struct graph_wall;

struct graph_table {
    struct object_trans trans;
    struct graph_wall *walls;
    size_t walls_num;
};

void graph_table_init(struct graph_table *table);

void draw_graph_table(const struct graph_table *table);

