#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>
#include <fstream>

struct GameState {
	int tick_count;
	int trees_available;
	int logs;
	int planks;
	int arborists;
	int lumberjacks;
	int sawyers;
};

void saveGame(const GameState& state, const std::string& filename);
void loadGame(GameState& state, const std::string& filename);

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

void handle_input(GameState& state) {
	if (_kbhit()) {
		char input = _getch();
		switch (input) {
			case 'a': // Add an arborist
				if (state.planks >= 5) {
					state.planks -= 5;
					state.arborists++;
					std::cout << "Added an arborist!" << std::endl;
				} else {
					std::cout << "Not enough planks to add an arborist!" << std::endl;
				}
				break;
			case 'l': // Add a lumberjack
				if (state.planks >= 5) {
					state.planks -= 5;
					state.lumberjacks++;
					std::cout << "Added a lumberjack!" << std::endl;
				} else {
					std::cout << "Not enough planks to add a lumberjack!" << std::endl;
				}
				break;
			case 's': // Add a sawyer
				if (state.planks >= 5) {
					state.planks -= 5;
					state.sawyers++;
					std::cout << "Added a sawyer!" << std::endl;
				} else {
					std::cout << "Not enough planks to add a sawyer!" << std::endl;
				}
				break;
			case 'q': // Quit the game
				std::cout << "Quitting the game..." << std::endl;
				saveGame(state, "savegame.txt");
				exit(0);
				break;
			default:
				break;
		}
	}
}

void saveGame(const GameState& state, const std::string& filename) {
	std::ofstream saveFile(filename);
	if (saveFile.is_open()) {
		saveFile << state.trees_available << std::endl;
		saveFile << state.logs << std::endl;
		saveFile << state.planks << std::endl;
		saveFile << state.arborists << std::endl;
		saveFile << state.lumberjacks << std::endl;
		saveFile << state.sawyers << std::endl;
		saveFile.close();
		std::cout << "Game saved!" << std::endl;
	} else {
		std::cout << "Unable to save game!" << std::endl;
	}
}

void loadGame(GameState& state, const std::string& filename) {
	std::ifstream loadFile(filename);
	if (loadFile.is_open()) {
		loadFile >> state.trees_available;
		loadFile >> state.logs;
		loadFile >> state.planks;
		loadFile >> state.arborists;
		loadFile >> state.lumberjacks;
		loadFile >> state.sawyers;
		loadFile.close();
		std::cout << "Game loaded!" << std::endl;
	} else {
		std::cout << "Unable to load game!" << std::endl;
	}
}

int main() {
	GameState state = {
		.tick_count = 0,
		.trees_available = 0,
		.logs = 0,
		.planks = 0,
		.arborists = 1,
		.lumberjacks = 1,
		.sawyers = 1
	};

	loadGame(state, "savegame.txt");

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time passing
		tick(state);
		tick_count++;
		if (tick_count % 60 == 0) {
			saveGame(state, "savegame.txt");
		}
		handle_input(state);
		std::cout << "Tick: " << tick_count << " | Trees: " << state.trees_available
				  << " | Logs: " << state.logs
			<< " | Planks: " << state.planks << std::endl;
		
	}

	return 0;
}