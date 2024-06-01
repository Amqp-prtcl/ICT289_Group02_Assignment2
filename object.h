#pragma once

#include "GL/freeglut.h"
#include "vector.h"

struct object_trans {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

void object_trans_reset(struct object_trans *obj);

void object_trans_apply(const struct object_trans *obj);

