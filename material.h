#pragma once

#include "vector.h"

struct material {
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    GLfloat shininess;
};

enum mat {
    DEFAULT,
    BALL,
    CUE,
    BOARD,
};

#define apply_mat(v) apply_material(get_mat((v)->mat))

const struct material * get_mat(enum mat m);

void apply_material(const struct material *mat);

