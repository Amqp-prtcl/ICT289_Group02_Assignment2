#include "phys_table.h"

void (*on_hole_event)(struct wall *w, struct ball *b);

static void wall_trigger();

static struct wall walls[] = {
    {
        {.3, 1, .3},
        { PLAYFIELD_LENGTH/2 + 0, 0,  PLAYFIELD_WIDTH/2 + 0},
        {-PLAYFIELD_LENGTH/2 - 0, 0,  PLAYFIELD_WIDTH/2 + 0},
        {-PLAYFIELD_LENGTH/2 - 0, 0, -PLAYFIELD_WIDTH/2 - 0},
        0, 1,
    },
    {
        {.6, .6, .6},
        { 3, -0.01,  2.5},
        {-3, -0.01,  2.5},
        {-3, -0.01, -2.5},
        0, 0,
        wall_trigger, 1,
    },
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,  PLAYFIELD_WIDTH/2.0,  PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,  PLAYFIELD_WIDTH/2.0, -PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2.0,  PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2.0, -PLAYFIELD_LENGTH/4),

    x_wall(PLAYFIELD_WIDTH - 2*HOLE_RADIUS, TABLE_HEIGHT,  PLAYFIELD_LENGTH/2.0, 0),
    x_wall(PLAYFIELD_WIDTH - 2*HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_LENGTH/2.0, 0),

    side_pocket(1,  1)
    side_pocket(1, -1)

    corner( 1,  1)
    corner(-1,  1)
    corner( 1, -1)
    corner(-1, -1)
};

static void wall_trigger(struct wall *w, struct ball *b) {
    if (on_hole_event != NULL)
        on_hole_event(w, b);
}

void phys_table_init(struct table *table) {
    table->filled=0;
    object_trans_reset(&table->trans);
    table->walls = walls;
    table->walls_num = sizeof(walls) / sizeof(struct wall);
    for (size_t i = 0; i < table->walls_num; i++)
        CHECK_WALL(walls + i);
}

void phys_table_roughness(const struct table *t, const GLfloat delta) {
    t->walls->friction_coef += delta;
}

GLfloat get_table_roughness(const struct table *t) {
    return t->walls->friction_coef;
}

