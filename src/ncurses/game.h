#pragma once

#include "../gol.h"

#include <stdbool.h>

typedef struct {
    mode_e mode;
    bool update;
    bool output;
} game_s;

extern game_s game;

void initialization(void);
void input(void);
void update(void);
void output(void);
void finalization(void);
