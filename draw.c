#include "ui.h"
#include "draw_cue.h"
#include "board.h"
#include "state.h"
#include "camera.h"
#include "scene_utils.h"
#include "graph_table.h"

#include "light.h"

static void move_for_menu() {
    Vector4 v;
    glGetFloatv(GL_VIEWPORT, v);
    glTranslatef(v[2]*0.40/2, v[3]/2+v[3]/6, 0);
    glScalef(0.5, 0.5, 1);
}

static void draw_ui(void) {
    Vector4 v;
    glGetFloatv(GL_VIEWPORT, v);
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

    glTranslatef(20, v[3]-70, 0);
    glScalef(0.3, 0.3, 1);
    ui_stroke("table roughness: %f\n", table_get_roughness(&board.table));
    ui_stroke("score: %zu\n", board.score);

    if (current_state == CUE_FORCE || current_state == RUNNING ||
            current_state == CUE_ANIM)
        ui_stroke("Cue force: %f", board.cue_force);

    ui_end();
}


static void draw_start_screen(void) {
    ui_begin();
    glColor3f(1, 0, 0);

    move_for_menu();

    ui_stroke("Start new game\n");
    glScalef(0.5, 0.5, 1);
    ui_stroke("Please enter amount of balls (includes white ball): %s\n",
            board.input);
    glTranslatef(0, -1, 0);
    if (board.err != NULL)
        ui_stroke("Cannot start game: %s", board.err);
        
    ui_end();
    glutSwapBuffers();
}

static void draw_end_screen(void) {
    ui_begin();
    glColor3f(1, 0, 0);

    move_for_menu();

    ui_stroke("Game ended!\n");
    glScalef(0.5, 0.5, 1);
    ui_stroke("your score: %zu\n", board.score);
    ui_stroke("press enter to restart or 'q' to quit...");

    ui_end();
    glutSwapBuffers();
}

void draw_scene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

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
    camera_apply_projection();
    apply_light();

    //drawAxis();
    //drawGrid(100/100, 100);

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);

    draw_table(&board.table);
    draw_graph_table(&board.graph_table);
    draw_cue(&board.cue);

    glPopMatrix();

    draw_ui();

    glutSwapBuffers();
}

