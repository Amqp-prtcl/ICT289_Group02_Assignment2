#include "input.h"
#include "cue.h"
#include "matrix.h"
#include "dbg.h"

#define CUE_RADIUS 0.0090
void cue_init(struct cue *cue) {
    cue->hit_ball.color[0] = 0;
    cue->hit_ball.color[1] = 1;
    cue->hit_ball.color[2] = 0;
    vector3_to_zero(cue->hit_ball.trans.position);
    vector3_to_zero(cue->hit_ball.trans.rotation);
    vector3_to_one(cue->hit_ball.trans.scale);
    cue->hit_ball.phys.radius = CUE_RADIUS;
    vector3_to_zero(cue->lookat);
    cue->hide = 0;
}

void (*anim_end_callback)(void) = NULL;

static struct cue *current_cue;
static GLfloat current_time;
static Vector3 start_pos;
static Vector3 end_pos;

static GLfloat get_speed(const GLfloat t) {
    GLfloat t_1, res, p2, p3;
    p2 = 1;
    p3 = 1;
    t_1 = 1-t;
    res = t*t*t*p3;
    res += 3*t_1*t*t*p2;
    return res;
}

#define ANIM_STAGE_1 0.3
#define ANIM_STAGE_2 0.5
#define ANIM_TRAVEL 0.25
void cue_tick_anim(GLfloat delta) {
    if (current_cue == NULL)
        return;
    current_time += delta;

    if (current_time > ANIM_STAGE_2) {
        if (anim_end_callback != NULL)
            anim_end_callback();
        vector3_copy(start_pos, current_cue->hit_ball.trans.position);
        current_cue = NULL;
        return;
    }
    if (current_time  < ANIM_STAGE_1) {
        vector3_lerp(start_pos, end_pos,
                get_speed(MAP(current_time, 0, ANIM_STAGE_1, 0, 1)),
                current_cue->hit_ball.trans.position);
        return;
    }
    vector3_lerp(end_pos, current_cue->lookat,
            get_speed(MAP(current_time, ANIM_STAGE_1, ANIM_STAGE_2, 0, 0.95)),
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
    vector3_affine(temp, -ANIM_TRAVEL, start_pos, end_pos);

    temp[1] = 0;
    vector3_normalize(temp, temp);
    vector3_scale(temp, speed, current_cue->hit_ball.phys.speed);
}

#define OFFSET 0.05
#define OFFSET_HEIGHT 0.005
void cue_place(struct cue *cue, const struct ball *b) {
    GLfloat d = vector3_norm(b->trans.position);
    vector3_affine(b->trans.position, OFFSET/d,
            b->trans.position,
            cue->hit_ball.trans.position);
    cue->hit_ball.trans.position[1] = BALL_RAD+OFFSET_HEIGHT;
    vector3_copy(b->trans.position, cue->lookat);
    vector3_affine(vector3_down, OFFSET_HEIGHT,
            cue->lookat, cue->lookat);
}

void cue_hide(struct cue *cue) {
    cue->hide = 1;
}

void cue_show(struct cue *cue) {
    cue->hide = 0;
}

#define ROT_SPEED 25
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

