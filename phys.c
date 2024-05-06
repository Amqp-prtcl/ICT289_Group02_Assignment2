#include "phys.h"
#include "ball.h"
#include "stdio.h"

#include "board.h"

void phys_reset(struct phys *phys) {
    phys->mass = 1;
    phys->radius = 1;
    vector3_to_zero(phys->speed);
}

/*
void apply_gravity(struct phys *phys, const GLfloat delta) {
    phys->speed[1] -= G_FORCE * delta;
}

void apply_speed(const struct phys *phys, struct object_trans *obj,
        const GLfloat delta) {
    obj->position[0] += phys->speed[0] * delta;
    obj->position[1] += phys->speed[1] * delta;
    obj->position[2] += phys->speed[2] * delta;
}

void apply_collision(struct phys *phys, struct object_trans *obj,
        const GLfloat delay) {
    if (obj->position[1] - phys->radius <= 0) {
        phys->speed[0] *= GROUND_BOUND_FRICTION;
        phys->speed[1] *= -GROUND_BOUND_FRICTION;
        phys->speed[2] *= GROUND_BOUND_FRICTION;
        obj->position[1] = phys->radius;
    }
}*/

void compute_next_pos(struct board *board, const GLfloat delta) {
    struct ball *b;
    for (size_t i = 0; i < board->balls_num; i++) {
        b = board->balls + i;

        b->trans.position[0] += b->phys.speed[0] * delta;
        b->trans.position[1] += b->phys.speed[1] * delta;
        b->trans.position[2] += b->phys.speed[2] * delta;
    }
}

static void apply_collision(struct ball *b1, struct ball *b2) {
    Vector3 dist, vr;
    GLfloat d, impulse;

    vector3_sub(b2->trans.position, b1->trans.position, dist);
    d = vector3_norm(dist);

    if (d >= get_ball_radius(b1) + get_ball_radius(b2))
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
            apply_collision(b1, board->balls+j);
    }
}

/*
    TOO HARD TO IMPLEMENT -- SCRAPPED


// The collision algorithm:
//
// The goal is to have a delta time independent simulation. By that I mean that
// we simply forward the trajectories by the delta time and then check for
// collision since if a lag spike happens, some balls might forward too much
// and skip some collisions resulting in a bad simulation.
//
// In order to resolve this problem, we can first compute all possible
// collisions that will happen if the balls simply rolled with thier speed
// during the dela time and if a collision happens we compute the time it takes
// for the event to happen.
//
// Once we have checked for all possible collisions and computed all the time
// offsets (with a negative value if a collision does not happen), we can find
// the lowest positive value (the first collision to happen in this delta time)
// and resolve it (updating the new ball positions and silumation times left)
// and we then search for a new smallest value in the table.
//
// Once all the values are negative, no collision will happen if we forward the
// simulation by the delta time left for each ball so we can apply the times
// left and end up with a delta independent simulation inside delta time.
//
// Note: This algorithm can be CPU-intensive but this should not be the case in
// normal conditions (with a small delta time).
//


static GLfloat test_ball_walls(const struct board *board,
        const struct ball *ball, const GLfloat delta) {

    GLfloat d1, d2, d3;
    const GLfoat rad = get_ball_radius(ball);
    

    if (d1 < )
    return -1;
}

static GLfloat test_ball_ball(const struct ball *b1, const struct ball *b2,
        const GLfloat delta) {
    return -1;
}

static void fill_pos_array(const struct board *board, Vector3 *pos) {
    for (size_t i = 0; i < board->balls_num; i++) {
        vector_copy(pos+i, board->balls[i].trans.position);
    }
}

static void fill_delta_array(const struct board *board, GLfloat *times,
        const GLfloat delta) {
    for (size_t i = 0; i < board->balls_num; i++) {
        times[i] = delta;
    }
}

//   |b1|b2|b3|b4|..|bn|
//---|--|--|--|--|--|--|
// b1|  |xx|xx|xx|..|xx|
// b2|     |xx|xx|..|xx|
// b3|        |xx|..|xx|
// b4|           |..|xx|
// ..|              |xx|
void fill_collide_table(const struct *board, const GLfloat delta,
        GLfloat *times, GLfloat *col_table, Vector3 *positions) {

    size_t c = 0;
    for (size_t i = 0; i < l; i++)
        for (size_t j = i; j < l; j++) {
            if (j == i) {
                col_table[c++] = test_ball_walls(balls+i, delta);
                // TODO test for wall collision
                continue;
            }
            //TODO test collision between balls i and j
        }
}
*/
