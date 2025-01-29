#include "grid.h"


Grid::Grid(int width, int height)
	: cells(std::vector<std::vector<Cell>>(height, std::vector<Cell>(width)))
{
}

int Grid::getWidth() const { return cells.empty() ? 0 : cells[0].size(); }
int Grid::getHeight() const { return cells.size(); }

void Grid::resize(int width, int height)
{
	cells.resize(height);
	for (int i = 0; i < height; i++) {
		cells[i].resize(width);
	}
}

const std::vector<std::vector<Cell>>& Grid::getCells() const {
	return cells;
}

void Grid::toggleCell(int x, int y) {
	cells[y][x].solid = !cells[y][x].solid;
}
