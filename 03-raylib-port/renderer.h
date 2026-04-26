#pragma once
#include "GameState.h"

void init_renderer(int width, int height, const char* title);
void close_renderer();
void draw_frame(const GameState& state);
bool handle_input(GameState& state);