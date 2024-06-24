#pragma once
#include "grid.h"
#include <vector>

class Pathfinder {
public:
	Pathfinder(Grid& grid) : m_grid(grid) {}
	virtual ~Pathfinder() = default;

	virtual std::vector<sf::Vector2i> findPath(const sf::Vector2i& start, const sf::Vector2i& end) = 0;

private:
	Grid& m_grid;
};