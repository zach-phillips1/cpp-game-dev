#include <iostream>

struct GameState {
	int trees_available;
	int logs;
	int planks;
	int arborists;
	int lumberjacks;
	int sawyers;
};


int main() {
	GameState state = {
		.trees_available = 100,
		.logs = 50,
		.planks = 10,
		.arborists = 5,
		.lumberjacks = 3,
		.sawyers = 2
	};
	std::cout << "Trees available: " << state.trees_available << std::endl;
	std::cout << "Logs: " << state.logs << std::endl;
	std::cout << "Planks: " << state.planks << std::endl;
	std::cout << "Arborists: " << state.arborists << std::endl;
	std::cout << "Lumberjacks: " << state.lumberjacks << std::endl;
	std::cout << "Sawyers: " << state.sawyers << std::endl;
	return 0;
}