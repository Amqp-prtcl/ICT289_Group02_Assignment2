#include "board.h"
#include "dbg.h"

// MOVEMENTS

static void apply_forces(const struct board *board, struct ball *b,
        const GLfloat delta) {
    Vector3 n;

    vector3_normalize(b->phys.speed, n);
    GLfloat scale = board->table_friction_coef/b->phys.mass * delta;
    vector3_scale(n, -scale, n);

    b->phys.speed[0] += n[0];
    b->phys.speed[1] += n[1];
    b->phys.speed[2] += n[2];
}

static void apply_speed(struct ball *b, const GLfloat delta) {
    Vector3 dv;
    vector3_scale(b->phys.speed, delta, dv);
    vector3_add(b->trans.position, dv, b->trans.position);
}

void board_compute_next_positions(struct board *board, const GLfloat delta) {
    struct ball *b;
    GLfloat coef = board->table_friction_coef;
    for (size_t i = 0; i < board->balls_num; i++) {
        b = board->balls + i;

        apply_forces(board, b, delta);
        apply_speed(b, delta);
    }
}

// COLLISIONS HANDLING

#define is_not_bound(a) a < 0 || a > 1
static void ball_wall_collision(struct ball *b, const struct wall *w) {
    Vector3 v1, v2;
    GLfloat imp;

    vector3_sub(b->trans.position, w->p2, v1);
    matrix_vector_mul(w->m, v1, v2);

    if (v2[2] < 0 || v2[2] > ball_get_radius(b) ||
            is_not_bound(v2[0]) || is_not_bound(v2[1]))
        return;

    //DBG_VEC(v2);
    //DBG_BALL(b);

    // imp will be negative
    imp = vector3_dot(b->phys.speed, w->normal);

    vector3_affine(w->normal, -2*imp, b->phys.speed, b->phys.speed);

    vector3_affine(w->normal, ball_get_radius(b)-v2[2],
            b->trans.position, b->trans.position);
}

static void ball_ball_collision(struct ball *b1, struct ball *b2) {
    Vector3 dist, vr;
    GLfloat d, impulse;

    vector3_sub(b2->trans.position, b1->trans.position, dist);
    d = vector3_norm(dist);

    if (d > ball_get_radius(b1) + ball_get_radius(b2))
        return;

    // normalize dist
    vector3_scale(dist, 1/d, dist);
    vector3_sub(b2->phys.speed, b1->phys.speed, vr);
    impulse = vector3_dot(dist, vr);

    vector3_affine(dist, impulse/b1->phys.mass,
            b1->phys.speed, b1->phys.speed);
    vector3_affine(dist, -impulse/b2->phys.mass,
            b2->phys.speed, b2->phys.speed);

    vector3_affine(dist, ball_get_radius(b1)-d,
            b1->trans.position, b1->trans.position);
}


void board_handle_collisions(struct board *board, const GLfloat delta) {
    struct ball *b1;
    for (size_t i = 0; i < board->balls_num; i++) {
        b1 = board->balls + i;
        for (size_t j = i+1; j < board->balls_num; j++)
            ball_ball_collision(b1, board->balls+j);
        for (size_t j = 0; j < board->walls_num; j++)
            ball_wall_collision(b1, board->walls + j);
    }
}

