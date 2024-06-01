#include "input.h"
#include "game.h"
#include "table.h"
#include "camera.h"
#include "state.h"
#include "ball_setup.h"

static void bruh(void* f) {
    board.cue.hit_ball.trans.position[1] = board.balls->trans.position[1];
    board.cue.hit_ball.phys.mass = BALL_MASS;
    ball_ball_collision(&board.cue.hit_ball, board.balls);
    game_set_state(RUNNING);
}

static void on_hole(struct wall *w, struct ball *b) {
    vector3_to_zero(b->phys.speed);
    b->trans.position[1] += 2;
    b->off = 1;
    if (board.score == board.balls_num - 1) {
        board.score += 1;
        game_set_state(WON);
        return;
    }
    if (b == board.balls) {
        game_set_state(LOST);
        return;
    }
    board.score += 1;
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
            free(board.textures);
            glutLeaveMainLoop();
            break;
        case START_SCREEN:
            if (board.balls != NULL) {
                free(board.balls);
                board.balls = NULL;
                board.balls_num = 0;
            }
            board.score = 0;
            board.err = NULL;
            board.input[2] = 0;
            board.input[0] = 0;
            break;
        case LOST:
        case WON:
            game_set_state(END_SCREEN);
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
#define ROUGHNESS_DELTA 1
static void game_tick(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, game_tick, curr_time);

    camera_handle_keyboard(delta);

    delta *= board.timescale;

    if (IS_STATE_IN_GAME) {
        cue_tick_anim(delta);
        tick_phys(delta);

        if (is_key_down('o'))
            edit_table_roughness(&board.table, ROUGHNESS_DELTA * delta);
        if (is_key_down('i'))
            edit_table_roughness(&board.table, -ROUGHNESS_DELTA * delta);
    }

    if (current_state == AIMING)
        cue_keyboard_handler(&board.cue, delta);

    if (current_state == CUE_FORCE) {
        if (is_key_up('r')) {
            game_set_state(CUE_ANIM);
            cue_start_anim(&board.cue, board.cue_force);
        } else {
            board.cue_force += FORCE_DELTA * delta;
            if (board.cue_force > FORCE_MAX)
                board.cue_force = FORCE_MAX;
        }
    }

    glutPostRedisplay();
}

void start_game() {
    glutTimerFunc(DELAY, game_tick, glutGet(GLUT_ELAPSED_TIME));
    game_set_state(START_SCREEN);
}

static const char err_no_char[] = "no input";
static const char err_invalid[] = "unable to parse input";
static const char err_low[] = "input too low!";
static const char err_high[] = "input too high!";

static void try_start_game() {
    if (board.input[0] == 0) {
        board.err = err_no_char;
        return;
    }
    ssize_t v;
    if (sscanf(board.input, "%zi", &v) != 1) {
        board.err = err_invalid;
        return;
    }
    if (v < 2) {
        board.err = err_low;
        return;
    }
    if (v > 30) {
        board.err = err_high;
        return;
    }

    board.balls_num = v;
    Vector3 origin = {.7, BALL_RAD+0.0001, 0};
    board.balls = create_start_ball_setup(v, origin, board.textures);
    game_set_state(AIMING);
}

static void add_key(unsigned char key) {
    if (key == 8) {
        if (board.input[1] == 0)
            board.input[0] = 0;
        board.input[1] = 0;
        return;
    }
    if (board.input[0] == 0) {
        board.input[1] = 0;
        board.input[0] = key;
        return;
    }
    if (board.input[1] == 0)
        board.input[1] = key;
}

void game_keyboard_event(unsigned char key) {
    if (current_state == START_SCREEN) {
        if ((key >= '0' && key <= '9') || key == 8) {// DEL key
            add_key(key);
            return;
        }
    }
    switch (key) {
        case 13:
            switch (current_state) {
                case PAUSED:
                    game_set_state(AIMING);
                    break;
                case START_SCREEN:
                    try_start_game();
                    break;
                case END_SCREEN:
                    game_set_state(START_SCREEN);
                    break;
                default:
                    game_set_state(PAUSED);
                    break;
            }
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
    on_hole_event = on_hole;

    board.timescale = 1.0;

    board.balls_num = 0;
    board.balls = NULL;
    board.textures = BallTexture;

    init_default_table(&board.table);
    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

    cue_init(&board.cue);
    anim_end_callback = bruh;
    //cue_place(&board.cue, board.balls);
}

