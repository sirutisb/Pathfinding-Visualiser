#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"

class GridRenderer
{
public:
	GridRenderer(const Grid& grid, float cellSize);

	void render(sf::RenderWindow& window);

	sf::VertexArray createGridVertex(const sf::Vector2i& gridSize);


private:
	const Grid& grid;
	float cellSize;

	sf::VertexArray gridVertexArray;
	sf::RectangleShape gridBg;

	int vertexWidth, vertexHeight;
	const static sf::Color gridBgColor;
};