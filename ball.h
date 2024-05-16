#pragma once

#include "vector.h"
#include "object.h"
#include "phys.h"

struct ball {
    Vector3 color;
    struct object_trans trans;
    struct phys phys;
};

#define ball_get_radius(b) (b)->trans.scale[0] * (b)->phys.radius

void draw_ball(const struct ball *ball);

