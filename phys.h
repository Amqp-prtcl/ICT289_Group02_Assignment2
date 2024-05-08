#pragma once

#include "vector.h"

struct phys {
    GLfloat mass;
    GLfloat radius;
    Vector3 speed;
};

static void phys_reset(struct phys *phys) {
    phys->mass = 1;
    phys->radius = 1;
    vector3_to_zero(phys->speed);
}

