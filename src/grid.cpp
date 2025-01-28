#include "grid.h"

Grid::Grid()
{
}

Grid::Grid(int width, int height)
	: cells(std::vector<std::vector<Cell>>(height, std::vector<Cell>(width)))
{
}

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

void toggleCell(int x, int y) {
	cells[y][x] = !cells[y][x];
}
