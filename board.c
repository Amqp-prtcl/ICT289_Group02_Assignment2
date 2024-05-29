#include "board.h"
#include "dbg.h"

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

// COLLISIONS HANDLING

#define is_not_bound(a) a < 0.0 || a > 1.0
static void ball_wall_collision(struct ball *b, struct wall *w,
        const Vector3 gravity, const GLfloat delta) {
    Vector3 v1, v2;
    GLfloat imp;

    vector3_sub(b->trans.position, w->p2, v1);
    matrix_vector_mul(w->m, v1, v2);

    if (v2[2] < -ball_get_radius(b) || v2[2] > ball_get_radius(b) ||
            is_not_bound(v2[0]) || is_not_bound(v2[1]))
        return;

    if (w->on_trigger != NULL) {
        DBG_PRINT("wall trigger\n");
        w->on_trigger(w, b);
    }
    if (w->is_trigger_only)
        return;

    vector3_affine(w->normal, SIGN(v2[2])*(ball_get_radius(b)-ABS(v2[2])),
            b->trans.position, b->trans.position);

    GLfloat frict_thresh = vector3_dot(gravity, w->normal);

    imp = vector3_dot(b->phys.speed, w->normal);
    if (imp <= frict_thresh + 0.01 && imp >= -frict_thresh - 0.01) {
        //DBG_PRINT("friction\n");
        vector3_affine(b->phys.speed, -w->friction_coef*delta,
                b->phys.speed, b->phys.speed);
        vector3_affine(w->normal, -imp,
                b->phys.speed, b->phys.speed);
        return;
    }

    //DBG_PRINT("collision\n");
    vector3_affine(w->normal, -2*imp, b->phys.speed, b->phys.speed);
    vector3_affine(b->phys.speed, -w->collision_coef,
            b->phys.speed, b->phys.speed);
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
        for (size_t j = 0; j < board->walls_num; j++)
            ball_wall_collision(b1, board->walls + j, gravity, delta);
        for (size_t j = 0; j < board->table.walls_num; j++)
            ball_wall_collision(b1, board->table.walls + j, gravity, delta);
    }
}

/*
static void update_cue(struct board *board, const GLfloat delta) {
}

static void cue_ball_collision(const struct cue *cue, struct board *board,
        const GLfloat delta) {
}
*/

