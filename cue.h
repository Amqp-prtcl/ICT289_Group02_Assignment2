#pragma once

#include "ball.h"

struct cue {
    struct ball hit_ball;
    Vector3 lookat;
};

void draw_cue(const struct cue *cue);
void cue_start_anim(struct cue *cue);

