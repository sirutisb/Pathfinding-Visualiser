#pragma once
#include "Grid.h"

class Pathfinder {
public:
	Pathfinder(Grid& grid);
	virtual ~Pathfinder() = 0;
	virtual void findPath() = 0;

private:
	Grid& m_grid;
};