#pragma once
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> find_path(
    const std::vector<std::vector<int>>& grid,
    std::pair<int, int> start,
    std::pair<int, int> goal
);

