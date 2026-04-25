#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>

struct GameState {
	int trees_available;
	int logs;
	int planks;
	int arborists;
	int lumberjacks;
	int sawyers;
};

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
			default:
				break;
		}
	}
}

int main() {
	GameState state = {
		.trees_available = 0,
		.logs = 0,
		.planks = 0,
		.arborists = 1,
		.lumberjacks = 1,
		.sawyers = 1
	};

	auto now = std::chrono::steady_clock::now();
	int tick_count = 0;

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time passing
		tick(state);
		handle_input(state);
		tick_count++;
		std::cout << "Tick: " << tick_count << " | Trees: " << state.trees_available
				  << " | Logs: " << state.logs
			<< " | Planks: " << state.planks << std::endl;
		
	}

	return 0;
}