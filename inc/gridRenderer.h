#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"

class GridRenderer
{
public:
	GridRenderer(const Grid& grid, float cellSize);

	void render(sf::RenderWindow& window);

	void updateGridVertices(const sf::Vector2i& gridSize);
	void updateCellVertices();


private:
	const Grid& grid;
	float cellSize;

	sf::VertexArray gridLines;
	sf::VertexArray obstacleVertices;

	sf::RectangleShape gridBg;

	int vertexWidth, vertexHeight;
	const static sf::Color GRID_BG_COLOR;
	const static sf::Color SOLID_CELL_COLOR;
};