#include "board.h"
#include "dbg.h"

struct board board;

// MOVEMENTS

static GLfloat apply_forces(struct ball *b, const GLfloat delta) {
    b->phys.speed[1] += -G_FORCE*delta;
    return vector3_norm(b->phys.speed);
}

// returns the nrom of the highest speed (in order to interpolate)
static void apply_speed(struct ball *b, const GLfloat delta) {
    Vector3 dv;
    vector3_scale(b->phys.speed, delta, dv);
    vector3_add(b->trans.position, dv, b->trans.position);
}

GLfloat board_apply_forces(struct board *board, const GLfloat delta) {
    GLfloat max_speed, speed;
    max_speed = -1;
    struct ball *b;
    for (size_t i = 0; i < board->balls_num; i++) {
        b = board->balls + i;
        if (!b->off && (speed = apply_forces(b, delta)) > max_speed)
            max_speed = speed;
    }
    return max_speed;
}

void board_compute_next_positions(struct board *board, const GLfloat delta) {
    struct ball *b;
    for (size_t i = 0; i < board->balls_num; i++) {
        b = board->balls + i;
        if (!b->off)
            apply_speed(b, delta);
    }
}

void board_handle_collisions(struct board *board, const Vector3 gravity,
        const GLfloat delta) {
    struct ball *b1;
    for (size_t i = 0; i < board->balls_num; i++) {
        b1 = board->balls + i;
        if (b1->off)
            continue;
        for (size_t j = i+1; j < board->balls_num; j++)
            if (!board->balls[j].off)
                ball_ball_collision(b1, board->balls+j);
        for (size_t j = 0; j < board->table.walls_num; j++)
            wall_ball_collision(board->table.walls + j, b1, gravity, delta);
    }
}

