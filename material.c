#include "material.h"


static const struct material default_mat = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1,
};

static const struct material ball_mat = {
    {0.00, 0.00, 0.00, 1.0},
    {0.01, 0.01, 0.01, 1.0},
    {0.50, 0.50, 0.50, 1.0},
    32.0,
};

static const struct material cue_mat = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1,
};

static const struct material board_mat = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1,
};

const struct material * get_mat(enum mat m) {
    switch (m) {
        case BALL:
            return &ball_mat;
        case CUE:
            return &cue_mat;
        case BOARD:
            return &board_mat;
        default:
            return &default_mat;
    }
}

void apply_material(const struct material *mat) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat->shininess);
}
