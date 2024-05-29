#include "input.h"
#include "game.h"
#include "table.h"
#include "camera.h"
#include "state.h"
#include "ball_setup.h"

//struct board board;

static void bruh(void* f) {
    board.cue.hit_ball.trans.position[1] = board.balls->trans.position[1];
    ball_ball_collision(&board.cue.hit_ball, board.balls);
    game_set_state(RUNNING);
}

static void on_state_event(enum game_state old, enum game_state new) {
    DBG_PRINT("game state event: %s -> %s\n",
            state_to_string(old), state_to_string(new));
    if (old == PAUSED)
        board.timescale = 1.0;
    switch (new) {
        case PAUSED:
            board.timescale = 0.0;
            break;
        case AIMING:
            show_cue(&board.cue);
            cue_place(&board.cue, board.balls);
            vector3_to_zero(board.balls->phys.speed);
            break;
        case CUE_FORCE:
            board.cue_force = 0;
            break;
        case RUNNING:
            hide_cue(&board.cue);
            break;
        case QUIT:
            free(board.balls);
            board.balls_num = 0;
            glutLeaveMainLoop();
            break;
        default:
            break;
    }
}

static void tick_phys(const GLfloat delta) {
    GLfloat sub_delta, max_speed, a;
    size_t b;
    Vector3 gravity = {0, G_FORCE*delta, 0};

    max_speed = board_apply_forces(&board, delta);
    sub_delta = (BALL_RAD/2)/max_speed * board.timescale;
    if (sub_delta > delta || sub_delta <= 0)
        sub_delta = delta;

    a = delta/sub_delta;
    b = (size_t)a + (((size_t)(a*10))%10 == 0 ? 0 : 1);
    sub_delta = delta/b;

    for (size_t i = 0; i < b; i++) {
        board_compute_next_positions(&board, sub_delta);
        board_handle_collisions(&board, gravity, sub_delta);
    }

    if (current_state == RUNNING && max_speed <= G_FORCE*delta)
        game_set_state(AIMING);

}

#define DELAY 1
#define FORCE_DELTA 2
static void game_tick(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, game_tick, curr_time);

    camera_handle_keyboard(delta);

    delta *= board.timescale;

    if (current_state != PAUSED) {
        cue_tick_anim(delta);
        tick_phys(delta);
    }


    if (current_state == AIMING)
        cue_keyboard_handler(&board.cue, delta);

    if (current_state == CUE_FORCE) {
        if (is_key_up('r')) {
            game_set_state(CUE_ANIM);
            cue_start_anim(&board.cue, board.cue_force);
        } else
            board.cue_force += FORCE_DELTA * delta;
    }

    glutPostRedisplay();
}

void start_game() {
    glutTimerFunc(DELAY, game_tick, glutGet(GLUT_ELAPSED_TIME));
}

void game_keyboard_event(unsigned char key) {
    switch (key) {
        case 13:
            if (current_state != PAUSED)
                game_set_state(PAUSED);
            else
                game_set_state(AIMING);
            break;
        case 'r':
        case 'R':
            if (current_state == AIMING)
                game_set_state(CUE_FORCE);
            break;
        case 'T':
        case 't':
            camera_toggle();
            break;
        case 'g':
            DBG_PRINT("'g' pressed\n");
            break;
        default:
            break;
    }
}

void game_init(GLuint* BallTexture) {
    on_state_change = on_state_event;

    board.timescale = 1.0;

    Vector3 origin = {.7, BALL_RAD+0.0001, 0};
    board.balls_num = 2;
    board.balls = create_start_ball_setup(board.balls_num, origin, BallTexture);

    init_default_table(&board.table);
    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

    cue_init(&board.cue);
    anim_end_callback = bruh;
    cue_place(&board.cue, board.balls);

    game_set_state(PAUSED);
}

