#pragma once

enum game_state {
    INIT,
    PAUSED,
    AIMING,
    CUE_FORCE,
    CUE_ANIM,
    RUNNING,
    QUIT,
};

const char *state_to_string(enum game_state state);

extern enum game_state current_state;

extern void (*on_state_change)(enum game_state old, enum game_state new);

void game_set_state(enum game_state);
