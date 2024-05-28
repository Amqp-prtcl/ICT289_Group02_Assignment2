#pragma once

#include "board.h"

extern struct board board;

void game_init();
void start_game();

void game_keyboard_event(unsigned char key);

