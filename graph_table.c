#include "graph_table.h"

static struct wall walls[] = {
    {
        {0, 0, 1},
        {0, 0, 0},
        {1, 1, 1},
        {1, 1, 0},
    }
};

void graph_table_init(struct table *table) {
    table->filled = 1;
    object_trans_reset(&table->trans);
    table->walls = walls;
    table->walls_num = sizeof(walls) / sizeof(struct wall);
    for (size_t i = 0; i < table->walls_num; i++)
        CHECK_WALL(walls + i);
}


