#pragma once

#include "vector.h"
#include "ball.h"
#include "wall.h"
#include "cue.h"
#include "table.h"

struct board {
    GLfloat width;
    GLfloat length;

    // the first one (index 0) is the white ball
    struct ball *balls;
    size_t balls_num;

    struct wall *walls;
    size_t walls_num;

    struct table table;

    struct cue cue;

    GLfloat timescale;
};

void board_compute_next_positions(struct board *board, const GLfloat delta);
void board_handle_collisions(struct board *board, const GLfloat delta);

