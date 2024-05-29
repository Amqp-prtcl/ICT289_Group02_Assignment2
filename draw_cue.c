#include "draw_cue.h"
#include "math.h"
#include "matrix.h"
#include "dbg.h"

static void get_angles(const struct cue *cue, Vector3 out) {
    Vector3 dir, a, rot = {0};
    GLfloat n, b, d, ax,ay;
    vector3_sub(cue->lookat, cue->hit_ball.trans.position, dir);
    /*glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(dir[0], dir[1], dir[2]);
    glEnd();*/

    a[0] = dir[0];
    a[1] = 0;
    a[2] = dir[2];
    n = vector3_norm(a);
    b = vector3_dot(vector3_backward, a);
    d = vector3_dot(vector3_right, a);
    ay = (float)acos(b/n) * 180/M_PI;
    if (d <= 0.0)
        ay *= -1.0;

    vector3_copy(dir, a);
    rot[1] = ay;
    matrix_rotate_vector(rot, a, dir);

    a[0] = 0;
    a[1] = dir[1];
    a[2] = dir[2];
    n = vector3_norm(a);
    b = vector3_dot(vector3_backward, a);
    d = vector3_dot(vector3_up, a);
    ax = (float)acos(b/n) * 180/M_PI;
    if (d <= 0.0)
        ax *= -1.0;

    out[0] = ax;
    out[1] = ay;
    out[2] = 0;
}

void draw_cue(const struct cue *cue) {
    if (cue->hide)
        return;
    Vector3 rot;
    GLfloat rad = ball_get_radius(&cue->hit_ball);
    glColor3fv(cue->hit_ball.color);
    glPushMatrix();

    object_trans_apply(&cue->hit_ball.trans);

    get_angles(cue, rot);
    glRotatef(rot[1]+180, 0, 1, 0);
    //DrawCircle(0, 0, .3, 15);
    glRotatef(rot[0], 1, 0, 0);
    //DrawCircle(0, 0, .3, 15);

    glutWireSphere(rad, 20, 20);
    glColor3f(255, 255, 0);
    glutWireCylinder(rad, 1.473, 12, 20);

    glPopMatrix();
}
