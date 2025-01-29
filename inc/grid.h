#pragma once
#include "cell.h"
#include <vector>

class Grid
{
public:
	Grid() = default;
	Grid(int width, int height);

	void resize(int width, int height);
	void clear();
	void toggleCell(int x, int y);

	int getWidth() const;
	int getHeight() const;

	const std::vector<std::vector<Cell>>& getCells() const;


private:
	std::vector<std::vector<Cell>> cells;
};