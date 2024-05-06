#pragma once

#include "vector.h"
#include "object.h"
#include "phys.h"

struct ball {
    Vector3 color;
    struct object_trans trans;
    struct phys phys;
};

static GLfloat get_ball_radius(const struct ball *b) {
    return b->trans.scale[0] * b->phys.radius;
}

static void get_ball_next_pos(const struct ball *b, const GLfloat delta,
        Vector3 out) {
    out[0] = b->trans.position[0] + b->phys.speed[0] * delta;
    out[1] = b->trans.position[1] + b->phys.speed[1] * delta;
    out[2] = b->trans.position[2] + b->phys.speed[2] * delta;
}
