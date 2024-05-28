#pragma once

#include "board.h"

extern struct board board;

void game_init(void);
void start_game(void);

void game_keyboard_event(unsigned char key);

