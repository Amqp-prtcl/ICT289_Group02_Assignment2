#include "cue.h"

void draw_cue(const struct cue *cue) {
    GLfloat rad = ball_get_radius(&cue->hit_ball);
    glColor3fv(cue->hit_ball.color);
    glPushMatrix();
    object_trans_apply(&cue->hit_ball.trans);
    glutWireSphere(rad, 20, 20);

    glColor3f(255, 255, 0);
    glutWireCylinder(rad, 1.473, 12, 20);

    glPopMatrix();
}

