#pragma once

#include "object.h"

struct camera {
    Vector3 pos;
    Vector3 rot;
    GLfloat fov;
    int last_x, last_y;
};

#ifdef DEBUG
extern struct camera current_camera;
#endif

void camera_apply(void);
void camera_apply_projection(void);
void camera_handle_keyboard(const GLfloat delta);
void camera_handle_mouse(int x, int y);
void camera_toggle(void);

