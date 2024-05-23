#include "cue.h"
#include "dbg.h"

static void cue_look_at(const struct cue *cue) {
    gluLookAt(
            0,//cue->hit_ball.trans.position[0],
            0,//cue->hit_ball.trans.position[1],
            0,//cue->hit_ball.trans.position[2],
            cue->lookat[0], cue->lookat[1], cue->lookat[2],
            0, -1, 0);
}

void draw_cue(const struct cue *cue) {
    GLfloat rad = ball_get_radius(&cue->hit_ball);
    glColor3fv(cue->hit_ball.color);
    glPushMatrix();

    object_trans_apply(&cue->hit_ball.trans);
    cue_look_at(cue);

    glutWireSphere(rad, 20, 20);
    glColor3f(255, 255, 0);
    glutWireCylinder(rad, 1.473, 12, 20);

    glPopMatrix();
}

#define MAP(x,a,b,c,d) (x-a) / (b-a) * (d-c) + c

#define DELAY 3

static struct cue *current_cue;
static GLfloat current_time;
static Vector3 start_pos;
static Vector3 end_pos;

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

static void tick_anim(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    current_time += delta;
    if (current_time > 1) {
        vector3_copy(start_pos, current_cue->hit_ball.trans.position);
        current_cue = NULL;
        return;
    }

    if (current_time  < .75) {
        vector3_lerp(start_pos, end_pos,
                get_speed(MAP(current_time, 0, .75, 0, 1)),
                current_cue->hit_ball.trans.position);
        goto next;
    }
    vector3_lerp(end_pos, start_pos,
            get_speed(MAP(current_time, .75, 1, 0, 1)),
            current_cue->hit_ball.trans.position);

next:
    glutTimerFunc(DELAY, tick_anim, curr_time);
}

void cue_start_anim(struct cue *cue) {
    GLfloat d;
    Vector3 temp;
    if (current_cue != NULL)
        return;
    current_time = 0;
    current_cue = cue;
    vector3_copy(cue->hit_ball.trans.position, start_pos);
    vector3_sub(cue->lookat, cue->hit_ball.trans.position, temp);
    d = vector3_norm(temp);
    vector3_affine(temp, -d*1.75, start_pos, end_pos);
    glutTimerFunc(DELAY, tick_anim, glutGet(GLUT_ELAPSED_TIME));
}
