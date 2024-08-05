#include "Grid.h"
#include "Config.h"

Grid::Grid(int width, int height)
	: m_width{0}
	, m_height{0}
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

void Grid::save(const std::string& filename)
{
}

void Grid::load(const std::string& filename)
{
}

void Grid::clear()
{
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			cells[i][j].solid = false;
		}
	}
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
	auto gv = createGridVertex({ m_width, m_height }, Config::NODE_SIZE);
	sf::RectangleShape grid_bg{ sf::Vector2f{ m_width * Config::NODE_SIZE, m_height * Config::NODE_SIZE } };
	grid_bg.setFillColor(sf::Color::Cyan);
	window.draw(grid_bg);

	sf::RectangleShape solid{ sf::Vector2f{Config::NODE_SIZE, Config::NODE_SIZE} };
	solid.setFillColor(sf::Color(45, 45, 45));
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			if (cells[i][j].solid) {
				solid.setPosition(sf::Vector2f{Config::NODE_SIZE * j, Config::NODE_SIZE * i});
				window.draw(solid);
			}
		}
	}

	window.draw(gv);
}

void Grid::toggle(sf::Vector2i pos)
{
	if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height)
		return;

	Cell& cell = cells[pos.y][pos.x];
	cell.solid = !cell.solid;
}
