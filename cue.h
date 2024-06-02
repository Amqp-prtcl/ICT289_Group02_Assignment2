#pragma once

#include "ball.h"

struct cue {
    struct ball hit_ball;
    Vector3 lookat;
    int hide;
};

extern void(*anim_end_callback)(void);

void cue_init(struct cue *cue);

void cue_start_anim(struct cue *cue, const GLfloat speed);
void cue_place(struct cue *cue, const struct ball *b);


void cue_hide(struct cue *cue);
void cue_show(struct cue *cue);

void cue_keyboard_handler(struct cue *cue, const GLfloat delta);
void cue_tick_anim(const GLfloat delta);

