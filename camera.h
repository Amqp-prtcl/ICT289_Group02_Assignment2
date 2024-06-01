#pragma once

#include "object.h"

struct camera {
    Vector3 pos;
    Vector3 rot;
    int last_x, last_y;
};

extern struct camera current_camera;

void init_camera(void);
void camera_apply(void);
void camera_handle_keyboard(const GLfloat delta);
void camera_handle_mouse(int x, int y);
void camera_toggle(void);

