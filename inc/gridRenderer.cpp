#include "gridRenderer.h"

GridRenderer::GridRenderer(const Grid& grid, float cellSize)
	: grid(grid)
	, cellSize(cellSize)
{
}

void GridRenderer::render(sf::RenderWindow& window) const
{
	sf::RectangleShape rect({ 300.f, 300.f });
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Cyan);
	window.draw(rect);
}
