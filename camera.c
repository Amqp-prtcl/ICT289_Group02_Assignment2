#include "camera.h"
#include "input.h"
#include "matrix.h"
#include "dbg.h"

// since it is the viewing point, all translations must be done in the
// opposite direction
struct camera current_camera;
struct camera camera_top = {
    {0, 1, 0},
    {90, 0, 0},
    0, 0,
};

static struct camera *w_camera = &current_camera;


void init_camera() {
    vector3_to_zero(current_camera.pos);
    vector3_to_zero(current_camera.rot);
    current_camera.last_x = 0;
    current_camera.last_y = 0;
}

void camera_apply() {
    glRotatef(w_camera->rot[0], 1, 0, 0);
    glRotatef(w_camera->rot[1], 0, 1, 0);
    glRotatef(w_camera->rot[2], 0, 0, 1);

    glTranslatef(-w_camera->pos[0],
            -w_camera->pos[1],
            -w_camera->pos[2]);
}

#define MOVE_SPEED 1
void camera_handle_keyboard(const GLfloat delta) {
    if (w_camera != &current_camera)
        return;
    Vector3 f, left;
    Vector3 rot = {0, current_camera.rot[1], 0};
    matrix_rotate_vector(rot, vector3_forward, f);
    matrix_rotate_vector(rot, vector3_left, left);
    if (is_key_down('w'))
        vector3_affine(f, delta,
                current_camera.pos, current_camera.pos);
    if (is_key_down('s'))
        vector3_affine(f, -delta,
                current_camera.pos, current_camera.pos);
    if (is_key_down('a'))
        vector3_affine(left, delta,
                current_camera.pos, current_camera.pos);
    if (is_key_down('d'))
        vector3_affine(left, -delta,
                current_camera.pos, current_camera.pos);
    if (is_key_down(' '))
        vector3_affine(vector3_up, delta,
                current_camera.pos, current_camera.pos);
    if (is_key_down('c'))
        vector3_affine(vector3_up, -delta,
                current_camera.pos, current_camera.pos);
}

void camera_handle_mouse(int x, int y) {
    if (w_camera != &current_camera)
        return;
    GLfloat dx = x - current_camera.last_x;
    GLfloat dy = y - current_camera.last_y;
    current_camera.last_x = x;
    current_camera.last_y = y;

    current_camera.rot[0] = CLAMP(current_camera.rot[0]+dy, -90, 90);
    dy = current_camera.rot[1]+dx;
    if (dy > 180) dy -= 360;
    if (dy < -180) dy += 360;
    current_camera.rot[1] = dy;
    //DBG_PRINT("[CAMERA] mouse event: {dx: %i, dy: %i}\n", dx, dy);
}

void camera_toggle() {
    if (w_camera == &current_camera)
        w_camera = &camera_top;
    else
        w_camera = &current_camera;
}
