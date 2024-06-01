#include "ui.h"
#include "draw_cue.h"
#include "board.h"
#include "state.h"
#include "camera.h"
#include "scene_utils.h"
#include "phys_table.h"

#include "light.h"

static void draw_ui(void) {
    ui_begin();
    glColor3f(1, 0, 0);

#ifdef DEBUG
    ui_printf("camera position: {x: %f, y: %f, z: %f}",
            current_camera.pos[0],
            current_camera.pos[1],
            current_camera.pos[2]);

    ui_printf("camera rotation: {x: %f, y: %f, z: %f}",
            current_camera.rot[0],
            current_camera.rot[1],
            current_camera.rot[2]);

    ui_printf("current state: %s", state_to_string(current_state));
#endif

    ui_printf("table roughness: %f", get_table_roughness(&board.phys_table));
    ui_printf("score: %zu", board.score);

    if (current_state == CUE_FORCE || current_state == RUNNING ||
            current_state == CUE_ANIM)
        ui_printf("Cue force: %f", board.cue_force);

    ui_end();
}

static void draw_start_screen(void) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    ui_begin();
    glColor3f(1, 0, 0);

    ui_printf("Start Game ?");
    ui_printf("please enter amount of balls: %s", board.input);
    if (board.err != NULL)
        ui_printf("Cannot start game: %s", board.err);

    ui_end();
    glutSwapBuffers();
}

static void draw_end_screen(void) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    ui_begin();
    glColor3f(1, 0, 0);

    ui_printf("Ended!");
    ui_printf("your score: %zu", board.score);
    ui_printf("press enter to restart or 'q' to quit...");

    ui_end();
    glutSwapBuffers();
}

void draw_scene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (current_state == END_SCREEN) {
        draw_end_screen();
        return;
    }
    if (current_state == START_SCREEN) {
        draw_start_screen();
        return;
    }

    glPushMatrix();

    camera_apply();
    apply_light();

    //drawAxis();
    //drawGrid(100/100, 100);

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);

    for (size_t i = 0; i < board.walls_num; i++)
        draw_wall(board.walls + i);

    draw_table(&board.phys_table);
    draw_table(&board.graph_table);
    draw_cue(&board.cue);

    glPopMatrix();

    draw_ui();

    glutSwapBuffers();
}
