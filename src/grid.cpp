#include "Grid.h"

Grid::Grid(int width, int height) : m_width{ 0 }, m_height{ 0 }
{
	resize(width, height);
}

void Grid::resize(int width, int height)
{
	m_width = width;
	m_height = height;
	cells.resize(height);
	for (std::vector<Cell>& row : cells)
		row.resize(width);
}

sf::VertexArray createGridVertex(const sf::Vector2i& gridSize, float cellSize) {
	sf::VertexArray grid(sf::Lines);

	// Create horizontal lines
	for (unsigned int i = 0; i <= gridSize.y; i++) {
		float y = i * cellSize;
		grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::White));
		grid.append(sf::Vertex(sf::Vector2f(gridSize.x * cellSize, y), sf::Color::White));
	}

	// Create vertical lines
	for (unsigned int j = 0; j <= gridSize.x; j++) {
		float x = j * cellSize;
		grid.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::White));
		grid.append(sf::Vertex(sf::Vector2f(x, gridSize.y * cellSize), sf::Color::White));
	}
	return grid;
}

void Grid::render(sf::RenderWindow& window)
{
	auto gv = createGridVertex({ m_width, m_height }, 45.0f);
	window.draw(gv);
}
