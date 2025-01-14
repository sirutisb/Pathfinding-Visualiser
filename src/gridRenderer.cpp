#include "gridRenderer.h"

const sf::Color GridRenderer::gridBgColor = sf::Color::Cyan;

GridRenderer::GridRenderer(const Grid& grid, float cellSize)
	: grid(grid)
	, cellSize(cellSize)
	, vertexWidth(0)
	, vertexHeight(0)
{
	gridBg.setFillColor(gridBgColor);
}

void GridRenderer::render(sf::RenderWindow& window)
{
	if (grid.getCells().size() == 0) return;
	int w = grid.getCells()[0].size();
	int h = grid.getCells().size();
	if (w != vertexWidth || h != vertexHeight) {
		vertexWidth = w;
		vertexHeight = h;
		gridVertexArray = createGridVertex({ vertexWidth, vertexHeight });
		gridBg.setSize(sf::Vector2f{ vertexWidth * cellSize, vertexHeight * cellSize });
	}

	window.draw(gridBg);
	window.draw(gridVertexArray);
}

sf::VertexArray GridRenderer::createGridVertex(const sf::Vector2i& gridSize)
{
	sf::VertexArray vertexArr(sf::PrimitiveType::Lines);

	// Create horizontal lines
	for (unsigned int i = 0; i <= gridSize.y; i++) {
		float y = i * cellSize;
		sf::Vertex vertex{{0, y}, sf::Color::White};
		vertexArr.append({{0, y}, sf::Color::White});
		vertexArr.append({{gridSize.x * cellSize, y}, sf::Color::White});
	}

	// Create vertical lines
	for (unsigned int j = 0; j <= gridSize.x; j++) {
		float x = j * cellSize;
		vertexArr.append({{x, 0}, sf::Color::White});
		vertexArr.append({{x, gridSize.y * cellSize}, sf::Color::White});
	}
	return vertexArr;
}
