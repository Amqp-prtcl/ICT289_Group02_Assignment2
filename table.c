#include "table.h"

static struct wall walls[] = {
    // table (full)
    {
        {1, 1, 1},
        {2.7432/2, 0, 1.3716/2},
        {-2.7432/2, 0, 1.3716/2},
        {-2.7432/2, 0, -1.3716/2},
    },
};

void init_default_table(struct table *table) {
    object_trans_reset(&table->trans);
    table->walls = walls;
    table->walls_num = sizeof(walls) / sizeof(struct wall);
    for (size_t i = 0; i < table->walls_num; i++)
        CHECK_WALL(walls + i);
}

void draw_table(const struct table *table) {
    glPushMatrix();
    object_trans_apply(&table->trans);
    for (size_t i = 0; i < table->walls_num; i++)
        draw_wall(table->walls + i);
    glPopMatrix();
}
