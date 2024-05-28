#include "ball.h"
#include "dbg.h"

void draw_ball(const struct ball *ball) {
    if (ball->off)
        return;
    //DBG_BALL(ball);
    glPushMatrix();
    glColor3fv(ball->color);
    object_trans_apply(&ball->trans);
    glutWireSphere(ball_get_radius(ball), 30, 30);
    glPopMatrix();
}

void ball_ball_collision(struct ball *b1, struct ball *b2) {
    Vector3 dist, vr;
    GLfloat d, impulse;

    vector3_sub(b2->trans.position, b1->trans.position, dist);
    d = vector3_norm(dist);

    if (d > ball_get_radius(b1) + ball_get_radius(b2))
        return;

    //DBG_PRINT("ball-ball collision!");
    // normalize dist
    vector3_scale(dist, 1/d, dist);
    vector3_sub(b2->phys.speed, b1->phys.speed, vr);
    impulse = vector3_dot(dist, vr);

    //impulse
    vector3_affine(dist, impulse,///b1->phys.mass,
            b1->phys.speed, b1->phys.speed);
    vector3_affine(dist, -impulse,///b2->phys.mass,
            b2->phys.speed, b2->phys.speed);

    vector3_affine(dist, -ball_get_radius(b1)-ball_get_radius(b2)+d,
            b1->trans.position, b1->trans.position);
}

