#pragma once

#include "vector.h"
#include "ball.h"

struct cue {
    struct ball hit_ball;
    Vector3 lookat;
    int hide;
};

extern void(*anim_end_callback)(void*);
extern void * cue_callback_arg;

void draw_cue(struct cue *cue);
//void cue_start_anim(struct cue *cue);
void cue_start_anim(struct cue *cue, const GLfloat speed);
void cue_place(struct cue *cue, const struct ball *b);

void cue_tick_anim(GLfloat delta);

void hide_cue(struct cue *cue);
void show_cue(struct cue *cue);

void cue_keyboard_handler(struct cue *cue, const GLfloat delta);

