#include "game.h"
#include "camera.h"
#include "state.h"

struct board board;

static void bruh(void* f) {
    ball_ball_collision(&board.cue.hit_ball, board.balls);
}

void game_init(void) {
    anim_end_callback = bruh;
    cue_place(&board.cue, board.balls);


    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

    board.timescale = 0;
}

void on_state_event(enum game_state old, enum game_state new) {
    on_state_change = on_state_event;
}

#define DELAY 1
static void game_tick(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, game_tick, curr_time);

    cue_tick_anim(delta);

    Vector3 gravity = {0, G_FORCE*delta*board.timescale, 0};
    GLfloat curr, max_speed, sub_delta;
    curr = 0;

    max_speed = board_apply_forces(&board, delta * board.timescale);
    sub_delta = (0.028)/max_speed * board.timescale;
    if (sub_delta > delta)
        sub_delta = delta;

    while (curr < delta && sub_delta > 0) {
        board_compute_next_positions(&board, sub_delta);
        board_handle_collisions(&board, gravity, delta);
        curr += sub_delta;
    }

    if (max_speed < G_FORCE*delta)
        cue_place(&board.cue, board.balls);

    camera_handle_keyboard(delta);

    glutPostRedisplay();
}

void start_game() {
    glutTimerFunc(DELAY, game_tick, glutGet(GLUT_ELAPSED_TIME));
}

void game_keyboard_event(unsigned char key) {
    switch (key) {
        case 13:
            if (board.timescale > 0)
                board.timescale = 0.0;
            else
                board.timescale = 1.0;
            break;
        case 'r':
        case 'R':
            cue_start_anim(&board.cue, 1);
            break;
        default:
            break;
    }
}
