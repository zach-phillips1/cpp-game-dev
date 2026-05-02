#include "astar.h"
#include "Node.h"
#include <iostream>

int main() {
	std::vector<std::vector<int>> grid = {
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0}
	};
	std::pair<int, int> start = {0, 0};
	std::pair<int, int> goal = {4, 4};
	std::vector<std::pair<int, int>> path = find_path(grid, start, goal);
	if (!path.empty()) {
		std::cout << "Path found:\n";
		for (const auto& [x, y] : path) {
			std::cout << "(" << x << ", " << y << ")\n";
		}
	} else {
		std::cout << "No path found.\n";
	}
	return 0;
}