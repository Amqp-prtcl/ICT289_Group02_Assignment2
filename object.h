#pragma once

#include "GL/freeglut.h"
#include "vector.h"

#define TRUE 1
#define FALSE 0

struct object_trans {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

void object_trans_reset(struct object_trans *obj);

void object_trans_apply(const struct object_trans *obj);

int object_trans_process_key(struct object_trans *obj,
        const unsigned char key);

int object_trans_process_special_key(struct object_trans *obj,
        const unsigned char key);

