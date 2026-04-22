#include <iostream>
#include <algorithm>

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
	std::cout << "Trees available: " << state.trees_available << std::endl;
	std::cout << "Logs: " << state.logs << std::endl;
	std::cout << "Planks: " << state.planks << std::endl;
	std::cout << "Arborists: " << state.arborists << std::endl;
	std::cout << "Lumberjacks: " << state.lumberjacks << std::endl;
	std::cout << "Sawyers: " << state.sawyers << std::endl;
	return 0;
}