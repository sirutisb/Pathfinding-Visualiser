#include "gridRenderer.h"

const sf::Color GridRenderer::GRID_BG_COLOR = sf::Color::Cyan;
const sf::Color GridRenderer::SOLID_CELL_COLOR = sf::Color(40, 40, 40);

GridRenderer::GridRenderer(const Grid& grid, float cellSize)
	: grid(grid)
	, cellSize(cellSize)
	, vertexWidth(0)
	, vertexHeight(0)
	, gridLines(sf::PrimitiveType::Lines)
{
	gridBg.setFillColor(GRID_BG_COLOR);
}

void GridRenderer::render(sf::RenderWindow& window)
{
	if (grid.getCells().size() == 0) return;
	int w = grid.getCells()[0].size();
	int h = grid.getCells().size();
	if (w != vertexWidth || h != vertexHeight) {
		vertexWidth = w;
		vertexHeight = h;
		updateGridVertices({ vertexWidth, vertexHeight });
		gridBg.setSize(sf::Vector2f{ vertexWidth * cellSize, vertexHeight * cellSize });
	}

	window.draw(gridBg);
	window.draw(gridLines);


	sf::VertexArray obstacleVertices(sf::PrimitiveType::Triangles);
	static float CELL_SIZE = 75.0f;
	// Populate the VertexArray with obstacle cells
	for (int row = 0; row < grid.getHeight(); ++row) {
		for (int col = 0; col < grid.getWidth(); ++col) {
			if (grid.getCells()[row][col].solid) {
				// Define the four corners of the cell
				sf::Vector2f topLeft(col * CELL_SIZE, row * CELL_SIZE);
				sf::Vector2f topRight((col + 1) * CELL_SIZE, row * CELL_SIZE);
				sf::Vector2f bottomRight((col + 1) * CELL_SIZE, (row + 1) * CELL_SIZE);
				sf::Vector2f bottomLeft(col * CELL_SIZE, (row + 1) * CELL_SIZE);

				// First triangle
				sf::Vertex vert;
				vert.color = sf::Color(50, 50, 50);
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
	}
	window.draw(obstacleVertices);

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
	//updateCellVertices();
}
