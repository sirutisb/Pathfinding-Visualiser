#pragma once
#include "pathfinder.h"

class DijkstraPathfinder : public Pathfinder {
public:
	DijkstraPathfinder(Grid& grid) : Pathfinder(grid) {}
	std::vector<sf::Vector2i> findPath(const sf::Vector2i& start, const sf::Vector2i& end) override;
};