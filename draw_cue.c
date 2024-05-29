#include "draw_cue.h"
#include "math.h"
#include "matrix.h"
#include "dbg.h"

#include "board.h"

#include "scene_utils.h"

static void set_clip_plane(const size_t plane, const struct wall *w,
        const GLdouble a, const GLdouble b) {
    const GLdouble p[] = {a*w->normal[0], a*w->normal[1], a*w->normal[2],
        b * vector3_dot(w->p2, w->normal)};

    glClipPlane(GL_CLIP_PLANE0 + plane, p);
}

static void draw_cue_overlay(const struct cue *cue) {
    glColor4f(0.7, 0.7, 0.7, 1);

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    draw_circle(0, 0, BALL_RAD*1.5, 30);
    glPopMatrix();

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);

    glColor4f(0.5, 0.5, 0.5, 1);
    glBegin(GL_POLYGON);
    glVertex3f(BALL_RAD, -0.001, 0);
    glVertex3f(-BALL_RAD, -0.001, 0);
    glVertex3f(-BALL_RAD, -0.001, -12);
    glVertex3f(BALL_RAD, -0.001, -12);
    glEnd();

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
}

static void get_angles(const Vector3 in, Vector3 out) {
    Vector3 a, rot = {0};
    GLfloat n, b, d, ax,ay;

    a[0] = in[0];
    a[1] = 0;
    a[2] = in[2];
    n = vector3_norm(a);
    b = vector3_dot(vector3_backward, a);
    d = vector3_dot(vector3_right, a);
    ay = (float)acos(b/n) * 180/M_PI;
    if (d <= 0.0)
        ay *= -1.0;

    rot[1] = ay;
    matrix_rotate_vector(rot, in, out);

    a[0] = 0;
    a[1] = out[1];
    a[2] = out[2];
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
    Vector3 dir, rot;
    GLfloat rad = ball_get_radius(&cue->hit_ball);
    glColor3fv(cue->hit_ball.color);
    glPushMatrix();

    set_clip_plane(0, board.table.walls + 1, 1, -1);
    set_clip_plane(1, board.table.walls + 3, -1, 1);
    set_clip_plane(2, board.table.walls + 5, 1, 1);
    set_clip_plane(3, board.table.walls + 6, -1, -1);
    object_trans_apply(&cue->hit_ball.trans);

    vector3_sub(cue->lookat, cue->hit_ball.trans.position, dir);


    get_angles(dir, rot);
    glRotatef(rot[1]+180, 0, 1, 0);
    //DrawCircle(0, 0, .3, 15);
    glPushMatrix();
    glRotatef(rot[0], 1, 0, 0);
    //DrawCircle(0, 0, .3, 15);

    glutWireSphere(rad, 20, 20);
    glColor3f(255, 255, 0);
    glutWireCylinder(rad, 1.473, 12, 20);
    glPopMatrix();

    glTranslatef(0, -cue->hit_ball.trans.position[1]+0.001, -vector3_norm(dir));
    draw_cue_overlay(cue);

    glPopMatrix();
}
