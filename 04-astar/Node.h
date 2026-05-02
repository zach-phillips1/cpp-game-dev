#pragma once

struct Node {
	int x; // x and y are the coordinates of the node in the grid
	int y;
	int g_cost; // g is the cost from the start node to this node
	int h_cost; // h is the heuristic cost from this node to the end node
	int f_cost; // f is the total cost (g + h)
	int parent_x = -1;
	int parent_y = -1;
};

