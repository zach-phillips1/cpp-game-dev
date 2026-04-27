#include "raylib.h"
#include "renderer.h"
#include "GameState.h"
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
	for (size_t y = 0; y < state.grid.size(); ++y) {
		for (size_t x = 0; x < state.grid[y].size(); ++x) {
			// Draw the grid based on the tile types
			Color tile_color = LIGHTGRAY;
			if (state.grid[y][x] == TileType::Arborist) tile_color = GREEN;
			else if (state.grid[y][x] == TileType::Lumberjack) tile_color = BROWN;
			else if (state.grid[y][x] == TileType::Sawyer) tile_color = ORANGE;
			DrawRectangle(300 + x * 32, 10 + y * 32, 30, 30, tile_color);
		}
	}
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
	case KEY_ONE: // Select arborist
		state.selected_building = TileType::Arborist;
		state.last_message = "Selected Arborist for placement.";
		return true;
	case KEY_TWO: // Select lumberjack
		state.selected_building = TileType::Lumberjack;
		state.last_message = "Selected Lumberjack for placement.";
		return true;
	case KEY_THREE: // Select sawyer
		state.selected_building = TileType::Sawyer;
		state.last_message = "Selected Sawyer for placement.";
		return true;
	}
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (state.selected_building != TileType::Empty && state.planks >= 5) {
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			int gridX = (mouseX - 300) / 32;
			int gridY = (mouseY - 10) / 32;
			if (gridX >= 0 && gridX < (int)state.grid[0].size() && gridY >= 0 && gridY < (int)state.grid.size()) {
				if (state.grid[gridY][gridX] == TileType::Empty) {
					state.grid[gridY][gridX] = state.selected_building;
					state.last_message = "Placed " + std::to_string(static_cast<int>(state.selected_building)) + " at (" + std::to_string(gridX) + ", " + std::to_string(gridY) + ")";
					if (state.selected_building == TileType::Arborist) state.arborists++;
					else if (state.selected_building == TileType::Lumberjack) state.lumberjacks++;
					else if (state.selected_building == TileType::Sawyer) state.sawyers++;
					state.planks -= 5;
					state.selected_building = TileType::Empty;
				}
				else {
					state.last_message = "Can't place on top of structure!";
				}
			}
		}
	}
	return true;
}