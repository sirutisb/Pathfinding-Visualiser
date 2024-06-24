#pragma once
#include "utils.h"

struct Cell
{

};

class Grid
{
public:
	Grid(Vec2i size) : m_size(size) {
		m_data = new Cell[size.x * size.y];
	}

	Cell& getCell(int x, int y) { return m_data[y * m_size.x + x]; }
	Cell& getCell(Vec2i pos) { return getCell(pos.x, pos.y); }


private:
	Cell* m_data;
	Vec2i m_size;
};