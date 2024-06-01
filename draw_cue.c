#include "draw_cue.h"
#include "math.h"
#include "matrix.h"
#include "dbg.h"

#include "table.h"

#include "scene_utils.h"

#define OVERLAY_OFFSET -0.001
#define OVERLAY_LENGTH 12.0

static void draw_cue_overlay(const struct cue *cue) {
    glColor4f(0.7, 0.7, 0.7, 1);

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    draw_circle(0, 0, BALL_RAD*1.5, 30);
    glPopMatrix();

    table_enable_clipping_planes();

    glColor4f(0.5, 0.5, 0.5, 1);
    glBegin(GL_POLYGON);
    glVertex3f(BALL_RAD, -OVERLAY_OFFSET, 0);
    glVertex3f(-BALL_RAD, -OVERLAY_OFFSET, 0);
    glVertex3f(-BALL_RAD, -OVERLAY_OFFSET, -OVERLAY_LENGTH);
    glVertex3f(BALL_RAD, -OVERLAY_OFFSET, -OVERLAY_LENGTH);
    glEnd();

    table_disable_clipping_planes();
}

#define CUE_LENGTH 1.473

void draw_cue(const struct cue *cue) {
    if (cue->hide)
        return;
    Vector3 dir, rot;
    GLfloat rad = ball_get_radius(&cue->hit_ball);

    glColor3fv(cue->hit_ball.color);
    glPushMatrix();

    table_load_clipping_planes();

    vector3_sub(cue->lookat, cue->hit_ball.trans.position, dir);
    matrix_vector_get_angles(dir, rot);

    object_trans_apply(&cue->hit_ball.trans);

    glRotatef(rot[1]+180, 0, 1, 0);

    glPushMatrix();
    glRotatef(rot[0], 1, 0, 0);

    glutWireSphere(rad, 20, 20);
    glColor3f(1, 1, 0);
    glutWireCylinder(rad, CUE_LENGTH, 12, 20);
    glPopMatrix();

    glTranslatef(0, -cue->hit_ball.trans.position[1]+0.01, -vector3_norm(dir));
    draw_cue_overlay(cue);

    glPopMatrix();
}
