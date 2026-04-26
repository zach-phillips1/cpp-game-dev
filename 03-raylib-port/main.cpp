#include "raylib.h"
#include "GameState.h"
#include "renderer.h"
#include <chrono>

int main() {
	GameState state = {0, 0, 0, 0, 1, 1, 1, ""};
	init_renderer(800, 600, "Lumber Tycoon");
	loadGame(state, "savegame.txt");
	auto last_tick = std::chrono::steady_clock::now();
	while (!WindowShouldClose()) {
		if (!handle_input(state)) break;
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - last_tick).count() >= 1) {
			tick(state);
			state.tick_count++;
			last_tick = now;
			if (state.tick_count % 60 == 0) {
				saveGame(state, "savegame.txt");
			}
		}
		draw_frame(state);
	}
	close_renderer();
	return 0;
}