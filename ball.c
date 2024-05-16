#include "ball.h"

void draw_ball(const struct ball *ball) {
    //DBG_BALL(ball);
    glColor3fv(ball->color);
    glPushMatrix();
    object_trans_apply(&ball->trans);
    glutWireSphere(ball_get_radius(ball), 30, 30);
    glPopMatrix();
}

