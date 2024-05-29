#include "ball_setup.h"
#include "dbg.h"

#include "stdlib.h"

#define COS30 0.86602540378

// BALL_RAD

static void align(struct ball *b, const size_t num,
        const GLfloat len_offset, const GLfloat y) {

    GLfloat side_offset = (num-1) * (BALL_RAD + 0.0001);

    Vector3 v = {len_offset, y, -side_offset};
    for (size_t i = 0; i < num; i++) {
        vector3_copy(v, b[i].trans.position);
        v[2] += 2 * BALL_RAD+0.001;
    }
}

struct ball * create_start_ball_setup(size_t ball_num, const Vector3 origin) {
    struct ball *res = malloc(ball_num * sizeof(struct ball));
    if (res == NULL || ball_num == 0)
        return NULL;

    struct ball *b;
    Vector3 c = {0, .6, .5};
    for (size_t i = 0; i < ball_num; i++) {
        b = res + i;

        vector3_copy(c, b->color);
        vector3_to_zero(b->trans.rotation);
        vector3_to_one(b->trans.scale);
        vector3_to_zero(b->phys.speed);
        b->phys.mass = BALL_MASS;
        b->phys.radius = BALL_RAD;
        b->off = 0;
    }

    GLfloat offset = origin[0];
    size_t a = 0;
    for (size_t i = 0; i < ball_num; i += a) {
        align(res+i, ++a, offset, origin[1]);
        offset += (2*(BALL_RAD+0.0001)) * COS30;
    }

    return res;
}
