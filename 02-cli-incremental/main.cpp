#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

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
		tick_count++;
		std::cout << "Tick: " << tick_count << " | Trees: " << state.trees_available
				  << " | Logs: " << state.logs
			<< " | Planks: " << state.planks << std::endl;
		
	}

	return 0;
}