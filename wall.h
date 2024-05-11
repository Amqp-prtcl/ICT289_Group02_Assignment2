#pragma once

#include "vector.h"
#include "matrix.h"
#include "dbg.h"

struct wall {
    Vector3 color;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    // 0 means no energy loss, higer values result in higer energy loos
    // on impact
    GLfloat collision_coef;

    // 0 means no friction, the higher the more friction
    GLfloat friction_coef;

    // should be automatically filled by CHECK_WALL()
    Vector3 p4;
    Vector3 normal;

    // |          |
    // | v1 v2 no |
    // |          |
    Matrix3x3 m;

    // if one or more of the three initial points (p1, p2 and/or p3) are
    // changed, you will probably need to set filled to false (0)
    int filled;
};

#define CHECK_WALL(w) if (!w->filled) precompute_wall(w);
void wall_init(struct wall *w);
