#include "material.h"
#include "dbg.h"

static const struct material default_mat = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1,
};

static const struct material ball_mat = {
    {0.25, 0.25, 0.25, 1.0},
    {0.4, 0.4, 0.4, 1.0},
    {0.9, 0.9, 0.9, 1.0},
    76.0,
};

static const struct material cue_mat = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1,
};

static const struct material board_mat = {
    {0.3, 0.7, 0.3, 1.0},
    {0.4, 0.5, 0.4, 1.0},
    {0.04, 0.07, 0.04, 1.0},
    10,
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
    //apply_light();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat->shininess);
}
