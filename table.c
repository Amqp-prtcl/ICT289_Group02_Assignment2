#include "table.h"

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
        {(dx)*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { 0.00           , 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { 0.00           , TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 0, 1},\
        {-(dx)*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { 0.00            , 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { 0.00            , TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 1, 1},\
        { (dx)*2*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        {-(dx)*2*HOLE_RADIUS, 0.0         , (dz)*TABLE_WIDTH/2.0},\
        {-(dx)*2*HOLE_RADIUS, TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 1, 1},\
        {-(dx)*2*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { (dx)*2*HOLE_RADIUS, 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { (dx)*2*HOLE_RADIUS, TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },

#define corner(dx, dz)\
    {\
        {0, 0, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 - HOLE_RADIUS), 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0)},\
        {(dx)*(TABLE_LENGTH/2.0 - HOLE_RADIUS)    , 0.0         ,\
            (dz)*(TABLE_WIDTH/2.0)},\
        {(dx)*(TABLE_LENGTH/2.0 - HOLE_RADIUS)    , TABLE_HEIGHT,\
            (dz)*(TABLE_WIDTH/2.0)},\
    },\
    {\
        {0, 0, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0), 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(TABLE_LENGTH/2.0)    , 0.0         ,\
            (dz)*(TABLE_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(TABLE_LENGTH/2.0)    , TABLE_HEIGHT,\
            (dz)*(TABLE_WIDTH/2.0 - HOLE_RADIUS)},\
    },\
    {\
        {1, 1, 1},\
        {(dx)*((PLAYFIELD_LENGTH + TABLE_LENGTH)/4.0), 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0)                 , 0.0         ,\
            (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0)                 , TABLE_HEIGHT,\
            (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), 0.0         ,\
            (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), TABLE_HEIGHT,\
            (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 - HOLE_RADIUS) , 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
        {(dx)*((PLAYFIELD_LENGTH+TABLE_LENGTH)/4.0), 0.0         ,\
            (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
        {(dx)*((PLAYFIELD_LENGTH+TABLE_LENGTH)/4.0), TABLE_HEIGHT,\
            (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
    },

void (*on_hole_event)(struct wall *w, struct ball *b);

static void wall_trigger();

static struct wall walls[] = {
    {
        {.3, 1, .3},
        { PLAYFIELD_LENGTH/2 + 0, 0,  PLAYFIELD_WIDTH/2 + 0},
        {-PLAYFIELD_LENGTH/2 - 0, 0,  PLAYFIELD_WIDTH/2 + 0},
        {-PLAYFIELD_LENGTH/2 - 0, 0, -PLAYFIELD_WIDTH/2 - 0},
        0.5, 1,
    },
    {
        {.6, .6, .6},
        { TABLE_LENGTH/2, -0.01,  TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, -0.01,  TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, -0.01, -TABLE_WIDTH/2},
        0, 0,
        wall_trigger, 1,
    },
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,
            PLAYFIELD_WIDTH/2.0,  PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,
            PLAYFIELD_WIDTH/2.0, -PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,
            -PLAYFIELD_WIDTH/2.0,  PLAYFIELD_LENGTH/4),
    z_wall(PLAYFIELD_LENGTH/2 - 2*HOLE_RADIUS, TABLE_HEIGHT,
            -PLAYFIELD_WIDTH/2.0, -PLAYFIELD_LENGTH/4),

    x_wall(PLAYFIELD_WIDTH - 2*HOLE_RADIUS, TABLE_HEIGHT,
            PLAYFIELD_LENGTH/2.0, 0),
    x_wall(PLAYFIELD_WIDTH - 2*HOLE_RADIUS, TABLE_HEIGHT,
            -PLAYFIELD_LENGTH/2.0, 0),

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

void draw_table(const struct table *table) {
    if (table->hide)
        return;
    glPushMatrix();
    object_trans_apply(&table->trans);
    for (size_t i = 0; i < table->walls_num; i++)
        draw_wall(table->walls + i);

    glPopMatrix();
}

void table_init(struct table *table) {
    object_trans_reset(&table->trans);
    table->walls = walls;
    table->walls_num = sizeof(walls) / sizeof(struct wall);
    for (size_t i = 0; i < table->walls_num; i++)
        CHECK_WALL(walls + i);
    table->hide = 1;
}

void table_show(struct table *t) {
    t->hide = 0;
}

void table_hide(struct table *t) {
    t->hide = 1;
}

void table_toggle(struct table *t) {
    t->hide = !t->hide;
}

void table_set_roughness(const struct table *t, const GLfloat delta) {
    t->walls->friction_coef += delta;
}

GLfloat table_get_roughness(const struct table *t) {
    return t->walls->friction_coef;
}

static void set_clip_plane(const size_t plane, const struct wall *w,
        const GLdouble a, const GLdouble b) {
    const GLdouble p[] = {a*w->normal[0], a*w->normal[1], a*w->normal[2],
        b * vector3_dot(w->p2, w->normal)};

    glClipPlane(GL_CLIP_PLANE0 + plane, p);
}

void table_load_clipping_planes() {
    set_clip_plane(0, walls + 2, 1, -1);
    set_clip_plane(1, walls + 4, -1, 1);
    set_clip_plane(2, walls + 6, 1, 1);
    set_clip_plane(3, walls + 7, -1, -1);
}

void table_enable_clipping_planes() {
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);
}

void table_disable_clipping_planes() {
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
}

