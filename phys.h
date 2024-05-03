#pragma once

#include "vector_math.h"
#include "object.h"

struct phys {
    GLfloat mass;
    GLfloat radius;
    Vector3 speed;
};

#define GROUND_BOUND_FRICTION 0.3
#define G_FORCE 9.81

void phys_reset(struct phys *phys);
void apply_gravity(struct phys *phys, const GLfloat delta);
void apply_speed(const struct phys *phys, struct object_trans *obj,
        const GLfloat delta);
void apply_collision(struct phys *phys, struct object_trans *obj,
        const GLfloat delay);
