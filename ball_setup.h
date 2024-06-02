#pragma once

#include "ball.h"

// must be manually freed after use
struct ball * create_start_ball_setup(size_t ball_num, const Vector3 origin,
    const GLuint *BallTexture);

