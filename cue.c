#include "input.h"
#include "cue.h"
#include "math.h"
#include "matrix.h"
#include "dbg.h"

static struct cue *current_cue;
static GLfloat current_time;
static Vector3 start_pos;
static Vector3 end_pos;
void (*anim_end_callback)(void*) = NULL;
void * cue_callback_arg = NULL;

static GLfloat get_speed(const GLfloat t) {
    GLfloat t_1, res, p2, p3; //p0, p1, p2, p3;
    //p0 = 0;
    //p1 = 0;
    p2 = 1;
    p3 = 1;
    t_1 = 1-t;
    res = t*t*t*p3;
    res += 3*t_1*t*t*p2;
    //res += 3*t_1*t_1*t*p1;
    //res += t_1*t_1*t_1*p0;
    return res;
}

#define OFFSET 0.05
void cue_place(struct cue *cue, const struct ball *b) {
    GLfloat d = vector3_norm(b->trans.position);
    vector3_affine(b->trans.position, OFFSET/d,
            b->trans.position,
            cue->hit_ball.trans.position);
    cue->hit_ball.trans.position[1] += 0.01;
    vector3_copy(b->trans.position, cue->lookat);
    vector3_affine(vector3_down, 0.001,
            cue->lookat, cue->lookat);
}

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

void draw_cue(struct cue *cue) {
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

void cue_tick_anim(GLfloat delta) {
    if (current_cue == NULL)
        return;
    current_time += delta;

    if (current_time > .5) {
        if (anim_end_callback != NULL)
            anim_end_callback(cue_callback_arg);
        vector3_copy(start_pos, current_cue->hit_ball.trans.position);
        current_cue = NULL;
        return;
    }
    if (current_time  < .3) {
        vector3_lerp(start_pos, end_pos,
                get_speed(MAP(current_time, 0, .30, 0, 1)),
                current_cue->hit_ball.trans.position);
        return;
    }
    vector3_lerp(end_pos, current_cue->lookat,
            get_speed(MAP(current_time, .30, .5, 0, 0.95)),
            current_cue->hit_ball.trans.position);
}

void cue_start_anim(struct cue *cue, const GLfloat speed) {
    Vector3 temp;
    if (current_cue != NULL)
        return;
    current_time = 0;
    current_cue = cue;

    vector3_copy(cue->hit_ball.trans.position, start_pos);
    vector3_sub(cue->lookat, cue->hit_ball.trans.position, temp);
    vector3_normalize(temp, temp);
    vector3_affine(temp, -.25, start_pos, end_pos);

    temp[1] = 0;
    vector3_normalize(temp, temp);
    vector3_scale(temp, speed, current_cue->hit_ball.phys.speed);
}

void hide_cue(struct cue *cue) {
    cue->hide = 1;
}

void show_cue(struct cue *cue) {
    cue->hide = 0;
}

#define ROT_SPEED 15
void cue_keyboard_handler(struct cue *cue, const GLfloat delta) {
    Vector3 rot = {0, ROT_SPEED * delta, 0};

    if (is_key_up('k') && is_key_up('l'))
        return;

    if (is_key_down('l'))
        rot[1] *= -1;

    matrix_rotate_vector_around_point(rot, cue->lookat,
            cue->hit_ball.trans.position,
            cue->hit_ball.trans.position);
}

