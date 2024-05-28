#pragma once

enum game_state {
    INIT,
    PAUSED,
    AIMING,
    CUE_ANIM,
    RUNNING,
};

extern enum game_state current_state;

extern void (*on_state_change)(enum game_state old, enum game_state new);

void game_set_state(enum game_state);
