#include "table.h"

void (*on_hole_event)(struct wall *w, struct ball *b);

#define table(lx, lz, y) {\
    {1, 0, 0},\
    {lx/2.0, y, lz/2.0},\
    {-lx/2.0, y, lz/2.0},\
    {-lx/2.0, y, -lz/2.0},\
},

#define x_wall(l, h, x, z) {\
    {1, 0, 0},\
    {x, 0, -(l)/2.0 + z},\
    {x, 0, (l)/2.0 + z},\
    {x, h, (l)/2.0 + z},\
}

#define z_wall(l, h, z, x) {\
    {1, 0, 0},\
    {-(l)/2.0 + x, 0, z},\
    {(l)/2.0 + x, 0, z},\
    {(l)/2.0 + x, h, z},\
}

#define side_pocket(dx, dz)\
    {\
        {0, 0, 1},\
        {(dx)*0.06, 0.0    , (dz)*1.27/2.0},\
        {     0.00, 0.0    , (dz)*1.63/2.0},\
        {     0.00, 0.05715, (dz)*1.63/2.0},\
    },\
    {\
        {0, 0, 1},\
        {-(dx)*0.06, 0.0    , (dz)*1.27/2.0},\
        {      0.00, 0.0    , (dz)*1.63/2.0},\
        {      0.00, 0.05715, (dz)*1.63/2.0},\
    },\
    {\
        {0, 1, 1},\
        { (dx)*0.12, 0.0    , (dz)*1.27/2.0},\
        {-(dx)*0.12, 0.0    , (dz)*1.63/2.0},\
        {-(dx)*0.12, 0.05715, (dz)*1.63/2.0},\
    },\
    {\
        {0, 1, 1},\
        {-(dx)*0.12, 0.0    , (dz)*1.27/2.0},\
        { (dx)*0.12, 0.0    , (dz)*1.63/2.0},\
        { (dx)*0.12, 0.05715, (dz)*1.63/2.0},\
    },

#define corner(dx, dz)\
    {\
        {0, 0, 1},\
        {(dx)*(2.54/2.0 - 0.06), 0.0    , (dz)*(1.27/2.0)},\
        {(dx)*(2.90/2.0 - 0.06), 0.0    , (dz)*(1.63/2.0)},\
        {(dx)*(2.90/2.0 - 0.06), 0.05715, (dz)*(1.63/2.0)},\
    },\
    {\
        {0, 0, 1},\
        {(dx)*(2.54/2.0), 0.0    , (dz)*(1.27/2.0 - 0.06)},\
        {(dx)*(2.90/2.0), 0.0    , (dz)*(1.63/2.0 - 0.06)},\
        {(dx)*(2.90/2.0), 0.05715, (dz)*(1.63/2.0 - 0.06)},\
    },\
    {\
        {1, 1, 1},\
        {(dx)*((2.54 + 2.90)/4.0), 0.0    , (dz)*(1.27/2.0)},\
        {(dx)*(2.54/2.0)         , 0.0    , (dz)*((1.27+1.63)/4.0)},\
        {(dx)*(2.54/2.0)         , 0.05715, (dz)*((1.27+1.63)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(2.54/2.0 + 0.06), 0.0    , (dz)*(1.27/2.0 - 0.06)},\
        {(dx)*(2.54/2.0 + 0.06), 0.0    , (dz)*((1.27+1.63)/4.0)},\
        {(dx)*(2.54/2.0 + 0.06), 0.05715, (dz)*((1.27+1.63)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(2.54/2.0 - 0.06), 0.0    , (dz)*(1.27/2.0 + 0.06)},\
        {(dx)*((2.54+2.9)/4.0) , 0.0    , (dz)*(1.27/2.0 + 0.06)},\
        {(dx)*((2.54+2.9)/4.0) , 0.05715, (dz)*(1.27/2.0 + 0.06)},\
    },

static void wall_trigger();

static struct wall walls[] = {
    // table (full)
    /*{
        {.3, .3, .3},
        {2.9/2, 0, 1.63/2},
        {-2.9/2, 0, 1.63/2},
        {-2.9/2, 0, -1.63/2},
        0, 0,
    },*/
    {
        {.3, 1, .3},
        { 2.540/2 + 0, 0,  1.270/2 + 0},
        {-2.540/2 - 0, 0,  1.270/2 + 0},
        {-2.540/2 - 0, 0, -1.270/2 - 0},
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
    z_wall(2.540/2 - 0.12, 0.05715,  1.27/2.0,  2.54/4),
    z_wall(2.540/2 - 0.12, 0.05715,  1.27/2.0, -2.54/4),
    z_wall(2.540/2 - 0.12, 0.05715, -1.27/2.0,  2.54/4),
    z_wall(2.540/2 - 0.12, 0.05715, -1.27/2.0, -2.54/4),
    x_wall(1.27 - 0.12, 0.05715,  2.54/2.0, 0),
    x_wall(1.27 - 0.12, 0.05715, -2.54/2.0, 0),

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

void edit_table_roughness(const struct table *t, const GLfloat delta) {
    t->walls->friction_coef += delta;
}

GLfloat get_table_roughness(const struct table *t) {
    return t->walls->friction_coef;
}
