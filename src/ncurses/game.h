#pragma once

#include "../gol.h"

#include <stdbool.h>

typedef struct {
    mode_e mode;
    bool update;
    bool output;
} game_s;

extern game_s game;

void game_initialization(void);
void game_input(void);
void game_update(void);
void game_output(void);
void game_finalization(void);
