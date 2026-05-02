#include "astar.h"
#include "Node.h"
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<int, int>> find_path(
	const std::vector<std::vector<int>>& grid,
	std::pair<int, int> start,
	std::pair<int, int> goal
) {
	std::vector<Node> open_list;
	std::vector<Node> closed_list;
	std::vector<std::pair<int, int>> directions = {
		{0, 1},  // right
		{1, 0},  // down
		{0, -1}, // left
		{-1, 0}  // up
	};

	// Initialize the start node
	int h = abs(start.first - goal.first) + abs(start.second - goal.second); // Manhattan distance heuristic
	Node start_node{start.first, start.second, 0, h, h, -1, -1};
	open_list.push_back(start_node);

	// Find the lowest f cost node in the open list
	while (!open_list.empty()) {
		int best_index = 0;
		for (int i = 1; i < open_list.size(); ++i) {
			if (open_list[i].f_cost < open_list[best_index].f_cost) {
				best_index = i;
			}
		}
		Node current_node = open_list[best_index];
		open_list.erase(open_list.begin() + best_index);

		// Checks to see if we have reached the goal
		if (current_node.x == goal.first && current_node.y == goal.second) {

			std::vector<std::pair<int, int>> path;
			path.push_back({ current_node.x, current_node.y });
			int px = current_node.parent_x;
			int py = current_node.parent_y;

			while (px != -1 && py != -1) {
				path.push_back({ px, py });
				auto it = std::find_if(closed_list.begin(), closed_list.end(), [&](const Node& node) {
					return node.x == px && node.y == py;
				});
				if (it != closed_list.end()) {
					px = it->parent_x;
					py = it->parent_y;
				} else {
					break;
				}
			}
			std::reverse(path.begin(), path.end());
			return path; // Return the path if the node is the goal node
		}
		closed_list.push_back(current_node);

		for (const auto& dir : directions) {
			int nx = current_node.x + dir.first;
			int ny = current_node.y + dir.second;

			if (nx < 0 || nx >= (int)grid[0].size() || ny < 0 || ny >= (int)grid.size() || grid[ny][nx] == 1) {
				continue; // Skip if out of bounds or an obstacle
			}
			if (std::find_if(closed_list.begin(), closed_list.end(), [&](const Node& node) {
				return node.x == nx && node.y == ny;
			}) != closed_list.end()) {
				continue; // Skip if in closed list
			}
			int g_cost = current_node.g_cost + 1;
			int h_cost = abs(nx - goal.first) + abs(ny - goal.second);
			int f_cost = g_cost + h_cost;

			Node neighbor{ nx, ny, g_cost, h_cost, f_cost, current_node.x, current_node.y };
			open_list.push_back(neighbor);
		}
	}
	return {};
}