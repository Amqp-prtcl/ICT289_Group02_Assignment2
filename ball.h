#pragma once

#include "vector.h"
#include "object.h"
#include "phys.h"

struct ball {
    Vector3 color;
    struct object_trans trans;
    struct phys phys;
};

static GLfloat ball_get_radius(const struct ball *b) {
    return b->trans.scale[0] * b->phys.radius;
}

