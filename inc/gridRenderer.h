#pragma once
#include <SFML/Graphics.hpp>
#include <grid.h>

class GridRenderer
{
public:
	GridRenderer(const Grid& grid, float cellSize);

	void render(const sf::RenderWindow& window) const; // maybe window shouldnt be const idk yet
private:
	const Grid& grid;
	float cellSize;
};