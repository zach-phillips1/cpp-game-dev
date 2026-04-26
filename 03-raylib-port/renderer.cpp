#include "raylib.h"
#include "renderer.h"
#include <string>

void init_renderer(int width, int height, const char* title) {
	InitWindow(width, height, title);
	SetTargetFPS(60);
}

void close_renderer() {
	CloseWindow();
}


void draw_frame(const GameState& state) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	// Display the game state on the screen
	DrawText(("Tick: " + std::to_string(state.tick_count)).c_str(), 10, 10, 20, BLACK);
	DrawText(("Trees Available: " + std::to_string(state.trees_available)).c_str(), 10, 40, 20, BLACK);
	DrawText(("Logs: " + std::to_string(state.logs)).c_str(), 10, 70, 20, BLACK);
	DrawText(("Planks: " + std::to_string(state.planks)).c_str(), 10, 100, 20, BLACK);
	DrawText(("Arborists: " + std::to_string(state.arborists)).c_str(), 10, 130, 20, BLACK);
	DrawText(("Lumberjacks: " + std::to_string(state.lumberjacks)).c_str(), 10, 160, 20, BLACK);
	DrawText(("Sawyers: " + std::to_string(state.sawyers)).c_str(), 10, 190, 20, BLACK);
	DrawText(state.last_message.c_str(), 10, 220, 20, DARKGREEN);
	EndDrawing();
}


bool handle_input(GameState& state) {
	switch (GetKeyPressed()) {
	case KEY_A: // Add an arborist
		if (state.planks >= 5) {
			state.planks -= 5;
			state.arborists++;
			state.last_message = "Added an arborist!";
		}
		else {
			state.last_message = "Not enough planks to add an arborist!";
		}
		return true;
	case KEY_L: // Add a lumberjack
		if (state.planks >= 5) {
			state.planks -= 5;
			state.lumberjacks++;
			state.last_message = "Added a lumberjack!";
		}
		else {
			state.last_message = "Not enough planks to add a lumberjack!";
		}
		return true;
	case KEY_S: // Add a sawyer
		if (state.planks >= 5) {
			state.planks -= 5;
			state.sawyers++;
			state.last_message = "Added a sawyer!";
		}
		else {
			state.last_message = "Not enough planks to add a sawyer!";
		}
		return true;
	case KEY_Q: // Quit the game
		state.last_message = "Quitting the game...";
		saveGame(state, "savegame.txt");
		return false;
	default:
		return true;
	}
	
}