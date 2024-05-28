#include "ui.h"
#include "draw.h"
#include "game.h"
#include "camera.h"
#include "scene_utils.h"

static void draw_ui() {
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);

    ui_begin(viewport);
    glColor3f(1, 0, 0);
    char *d;
    asprintf(&d, "camera position: {x: %f, y: %f, z: %f}",
            current_camera.pos[0],
            current_camera.pos[1],
            current_camera.pos[2]);
    free(d);
    ui_draw_text(d, 0, 20, viewport);
    asprintf(&d, "camera rotation: {x: %f, y: %f, z: %f}",
            current_camera.rot[0],
            current_camera.rot[1],
            current_camera.rot[2]);
    free(d);
    ui_draw_text(d, 0, 0, viewport);
    ui_end();
    return;
}

void draw_scene(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    camera_apply();
    drawAxis();
    //drawGrid(100/100, 100);

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);
    for (size_t i = 0; i < board.walls_num; i++)
        draw_wall(board.walls + i);

    draw_table(&board.table);
    draw_cue(&board.cue);
    glPopMatrix();

    draw_ui();

    glutSwapBuffers();
}
