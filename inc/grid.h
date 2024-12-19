#pragma once
#include "cell.h"
#include <vector>

class Grid
{
public:
	Grid();
	Grid(int width, int height);

	void resize(int width, int height);

	const std::vector<std::vector<Cell>>& getCells() const;

private:
	std::vector<std::vector<Cell>> cells;
};