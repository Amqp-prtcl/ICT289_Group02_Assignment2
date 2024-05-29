#include "stddef.h"
#include "state.h"

enum game_state current_state = INIT;

void (*on_state_change)(enum game_state old, enum game_state new) = NULL;

void game_set_state(enum game_state new_state) {
    if (current_state == new_state)
        return;

    enum game_state old = current_state;
    current_state = new_state;
    if (on_state_change != NULL) {
        on_state_change(old, new_state);
    }
}

const char *state_to_string(enum game_state state) {
    switch (state) {
        case INIT:
            return "INIT";
        case PAUSED:
            return "PAUSED";
        case AIMING:
            return "AIMING";
        case CUE_FORCE:
            return "CUE_FORCE";
        case CUE_ANIM:
            return "CUE_ANIM";
        case RUNNING:
            return "RUNNING";
        case QUIT:
            return "QUIT";
        default:
            return "UNKNOWN_STATE";
    }
}

