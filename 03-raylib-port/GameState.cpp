#include <iostream>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include "GameState.h"

void tick(GameState& state) {
	// Simulate the passage of time and update the game state
	state.trees_available += state.arborists; // Arborists plant new trees

	if (state.trees_available > 0) {
		int trees_to_cut = std::min(state.trees_available, state.lumberjacks);
		state.trees_available -= trees_to_cut; // Lumberjacks cut down trees
		state.logs += trees_to_cut; // Cut trees become logs
	}
	if (state.logs > 0) {
		int logs_to_process = std::min(state.logs, state.sawyers);
		state.logs -= logs_to_process; // Logs are used to make planks
		state.planks += logs_to_process; // Sawyers turn logs into planks
	}
}

void saveGame(const GameState& state, const std::string& filename) {
	std::ofstream saveFile(filename);
	if (saveFile.is_open()) {
		saveFile << state.tick_count << std::endl;
		saveFile << state.trees_available << std::endl;
		saveFile << state.logs << std::endl;
		saveFile << state.planks << std::endl;
		saveFile << state.arborists << std::endl;
		saveFile << state.lumberjacks << std::endl;
		saveFile << state.sawyers << std::endl;
		saveFile << state.grid.size() << " " << state.grid[0].size() << std::endl;
		for (const auto& row : state.grid) {
			for (const auto& tile : row) {
				saveFile << static_cast<int>(tile) << " ";
			}
			saveFile << std::endl;
		}
		saveFile.close();
		std::cout << "Game saved!" << std::endl;
	}
	else {
		std::cout << "Unable to save game!" << std::endl;
	}
}

void loadGame(GameState& state, const std::string& filename) {
	std::ifstream loadFile(filename);
	if (!loadFile.is_open()) {
		std::cout << "Unable to load game!" << std::endl;
		return;
	}

	if (!(loadFile >> state.tick_count
				 >> state.trees_available
				 >> state.logs
				 >> state.planks
				 >> state.arborists
				 >> state.lumberjacks
				 >> state.sawyers)) {
		std::cout << "Save file header corrupted." << std::endl;
		return;
	}

	const size_t MAX_ROWS = 1000;
	const size_t MAX_COLS = 1000;
	size_t rows = 0, cols = 0;
	if (!(loadFile >> rows >> cols)) {
		std::cout << "Save file missing dimensions." << std::endl;
		return;
	}

	if (rows == 0 || cols == 0 || rows > MAX_ROWS || cols > MAX_COLS) {
		std::cout << "Save file has invalid grid size." << std::endl;
		return;
	}

	state.grid.assign(rows, std::vector<TileType>(cols, TileType::Empty));

	for (size_t y = 0; y < rows; ++y) {
		for (size_t x = 0; x < cols; ++x) {
			int tile = 0;
			if (!(loadFile >> tile)) {
				std::cout << "Save file tile data truncated." << std::endl;
				return;
			}
			if (tile < 0 || tile > static_cast<int>(TileType::Arborist)) {
				tile = static_cast<int>(TileType::Empty); // sanitize out-of-range
			}
			state.grid[y][x] = static_cast<TileType>(tile);
		}
	}

	std::cout << "Game loaded!" << std::endl;
}