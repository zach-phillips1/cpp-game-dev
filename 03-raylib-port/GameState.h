#pragma once
#include <string>

struct GameState {
    int tick_count;
    int trees_available;
    int logs;
    int planks;
    int arborists;
    int lumberjacks;
    int sawyers;
    std::string last_message;
};

void tick(GameState& state);
void saveGame(const GameState& state, const std::string& filename);
void loadGame(GameState& state, const std::string& filename);
bool handle_input(GameState& state);