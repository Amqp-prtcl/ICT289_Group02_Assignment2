#include "ui.h"
#include "draw_cue.h"
#include "game.h"
#include "state.h"
#include "camera.h"
#include "scene_utils.h"

#include "light.h"

static int y_offset;

static void ui_printf(GLfloat *viewport, char *fmt, ...) {
    va_list v;
    va_start(v, fmt);
    glColor3f(1, 0, 0);

    char *d;
    vasprintf(&d, fmt, v);
    ui_draw_text(d, 0, y_offset, viewport);
    y_offset += 20;
    free(d);
    va_end(v);
}

static void draw_ui() {
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);

    ui_begin(viewport);
    y_offset = 20;
    glColor3f(1, 0, 0);
    ui_printf(viewport, "camera position: {x: %f, y: %f, z: %f}",
            current_camera.pos[0],
            current_camera.pos[1],
            current_camera.pos[2]);

    ui_printf(viewport, "camera rotation: {x: %f, y: %f, z: %f}",
            current_camera.rot[0],
            current_camera.rot[1],
            current_camera.rot[2]);

    ui_printf(viewport, "current state: %s", state_to_string(current_state));

    if (current_state == CUE_FORCE || current_state == RUNNING ||
            current_state == CUE_ANIM)
        ui_printf(viewport, "Cue force: %f", board.cue_force);

    ui_end();
    return;
}

void draw_scene(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    camera_apply();
    apply_light();
    //drawAxis();
    //drawGrid(100/100, 100);

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);
    for (size_t i = 0; i < board.walls_num; i++)
        draw_wall(board.walls + i);

    draw_table(&board.table);
    draw_cue(&board.cue);

    //draw_texture(texture_id);

    glPopMatrix();


    draw_ui();

    glutSwapBuffers();
}
