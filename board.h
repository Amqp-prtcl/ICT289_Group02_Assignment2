#pragma once

#include "vector.h"
#include "ball.h"


struct board {
    GLfloat width;
    GLfloat length;


    // the first one (index 0) is the white ball
    struct ball *balls;
    size_t balls_num;

};


