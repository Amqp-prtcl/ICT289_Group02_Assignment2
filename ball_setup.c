#include "ball_setup.h"

#include "stdlib.h"

static void align(struct ball *b, const size_t num) {
    
}

struct ball * create_start_ball_setup(size_t ball_num) {
    struct ball *res = malloc(ball_num * sizeof(struct ball));
    if (res == NULL)
        return res;

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

    return res;
}
