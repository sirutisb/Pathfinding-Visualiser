#include "gridRenderer.h"

const sf::Color GridRenderer::GRID_BG_COLOR = sf::Color::Cyan;
const sf::Color GridRenderer::SOLID_CELL_COLOR = sf::Color(40, 40, 40);

GridRenderer::GridRenderer(const Grid& grid, float cellSize)
	: grid(grid)
	, cellSize(cellSize)
	, gridLines(sf::PrimitiveType::Lines)
	, obstacleVertices(sf::PrimitiveType::Triangles)
	, vertexWidth(0)
	, vertexHeight(0)
{
	gridBg.setFillColor(GRID_BG_COLOR);
}

float GridRenderer::getCellSize() const { return cellSize; }

void GridRenderer::render(sf::RenderWindow& window)
{
	int w = grid.getWidth();
	int h = grid.getHeight();
	if (w != vertexWidth || h != vertexHeight) {
		vertexWidth = w;
		vertexHeight = h;
		updateGridVertices({ vertexWidth, vertexHeight });
		gridBg.setSize(sf::Vector2f{ vertexWidth * cellSize, vertexHeight * cellSize });
	}

	window.draw(gridBg);
	window.draw(obstacleVertices);
	window.draw(gridLines);
}

void GridRenderer::updateGridVertices(const sf::Vector2i& gridSize)
{
	gridLines.clear();

	// Create horizontal lines
	for (int i = 0; i <= gridSize.y; i++) {
		float y = i * cellSize;
		sf::Vertex vertex{{0, y}, sf::Color::White};
		gridLines.append({{0, y}, sf::Color::White});
		gridLines.append({{gridSize.x * cellSize, y}, sf::Color::White});
	}

	// Create vertical lines
	for (int j = 0; j <= gridSize.x; j++) {
		float x = j * cellSize;
		gridLines.append({{x, 0}, sf::Color::White});
		gridLines.append({{x, gridSize.y * cellSize}, sf::Color::White});
	}
	updateCellVertices();
}

void GridRenderer::updateCellVertices() {
	obstacleVertices.clear();
	const auto& cells = grid.getCells();
	for (const auto& key : cells) {
		const int x = key >> 16;
		const int y = key & 0xffff;
		// Define the four corners of the cell
		sf::Vector2f topLeft(x * cellSize, y * cellSize);
		sf::Vector2f topRight((x + 1) * cellSize, y * cellSize);
		sf::Vector2f bottomRight((x + 1) * cellSize, (y + 1) * cellSize);
		sf::Vector2f bottomLeft(x * cellSize, (y + 1) * cellSize);

		// First triangle
		sf::Vertex vert;
		vert.color = SOLID_CELL_COLOR;
		vert.position = topLeft;
		obstacleVertices.append(vert);
		vert.position = topRight;
		obstacleVertices.append(vert);
		vert.position = bottomRight;
		obstacleVertices.append(vert);

		// Second triangle
		vert.position = topLeft;
		obstacleVertices.append(vert);
		vert.position = bottomRight;
		obstacleVertices.append(vert);
		vert.position = bottomLeft;
		obstacleVertices.append(vert);
	}
}
