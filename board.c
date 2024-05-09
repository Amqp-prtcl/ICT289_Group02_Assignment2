#include "board.h"

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

    //vector3_scale(dv, -get_ball_radius(b)*3.1314, dv);
    //vector3_add(b->trans.rotation, dv, b->trans.rotation);
}

void compute_next_pos(struct board *board, const GLfloat delta) {
    struct ball *b;
    GLfloat coef = board->table_friction_coef;
    for (size_t i = 0; i < board->balls_num; i++) {
        b = board->balls + i;

        apply_forces(board, b, delta);
        apply_speed(b, delta);
    }
}

static void ball_wall_collision(struct ball *b, const struct wall *w) {
    return;
    Vector3 c;
    GLfloat d, imp;

    d = get_dist_from_plane(w, b->trans.position);
    if (d > get_ball_radius(b))
        return;

    vector3_affine(w->normal, d, b->trans.position, c);
    if (!is_point_on_wall(w, c))
        return;

    // imp will be negative
    imp = vector3_dot(b->phys.speed, w->normal);

    vector3_affine(w->normal, -imp, b->phys.speed, b->phys.speed);
}

static void ball_ball_collision(struct ball *b1, struct ball *b2) {
    Vector3 dist, vr;
    GLfloat d, impulse;

    vector3_sub(b2->trans.position, b1->trans.position, dist);
    d = vector3_norm(dist);

    if (d > get_ball_radius(b1) + get_ball_radius(b2))
        return;

    // normalize dist
    vector3_scale(dist, 1/d, dist);
    vector3_sub(b2->phys.speed, b1->phys.speed, vr);
    impulse = vector3_dot(dist, vr);

    vector3_affine(dist, impulse/b1->phys.mass,
            b1->phys.speed, b1->phys.speed);
    vector3_affine(dist, -impulse/b2->phys.mass,
            b2->phys.speed, b2->phys.speed);
}


void apply_collisions(struct board *board, const GLfloat delta) {
    struct ball *b1;
    for (size_t i = 0; i < board->balls_num; i++) {
        b1 = board->balls + i;
        for (size_t j = i+1; j < board->balls_num; j++)
            ball_ball_collision(b1, board->balls+j);
        for (size_t j = 0; j < board->walls_num; j++)
            ball_wall_collision(b1, board->walls + j);
    }
}

