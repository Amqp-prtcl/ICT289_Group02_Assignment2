#pragma once

#include "ball.h"

struct cue {
    struct ball hit_ball;
};

void draw_cue(const struct cue *cue);

