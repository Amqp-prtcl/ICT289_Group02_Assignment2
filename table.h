#pragma once

#include "object.h"
#include "wall.h"

#include "table_const.h"

struct table {
    struct object_trans trans;
    struct wall *walls;
    size_t walls_num;
    int hide;
};

extern void (*on_hole_event)(struct wall *w, struct ball *b);

void draw_table(const struct table *table);
void table_init(struct table *table);

void table_show(struct table *t);
void table_hide(struct table *t);
void table_toggle(struct table *t);

void table_set_roughness(const struct table *t, const GLfloat delta);
GLfloat table_get_roughness(const struct table *t);

void table_load_clipping_planes(void);
void table_enable_clipping_planes(void);
void table_disable_clipping_planes(void);

