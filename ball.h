#pragma once

#include "vector.h"
#include "object.h"
#include "phys.h"
#include "texture.h"

#define BALL_RAD 0.028
#define BALL_MASS 0.160

struct ball {
    Vector3 color;
    GLuint texture;
    struct object_trans trans;
    struct phys phys;
    int off;
};

#define ball_get_radius(b) ((b)->trans.scale[0] * (b)->phys.radius)

void drawTextureSphere(float radius, int slices, int stacks);

void draw_ball(const struct ball *ball);

void ball_ball_collision(struct ball *b1, struct ball *b2);

