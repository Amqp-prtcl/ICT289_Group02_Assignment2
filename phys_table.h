#pragma once

#include "table.h"

extern void (*on_hole_event)(struct wall *w, struct ball *b);

void phys_table_init(struct table *table);
void phys_table_roughness(const struct table *t, const GLfloat delta);
GLfloat get_table_roughness(const struct table *t);

