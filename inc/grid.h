#pragma once
#include <cstdint>

#include "cell.h"
#include <unordered_set>

class Grid
{
public:
	Grid();
	Grid(int width, int height);

	void resize(int width, int height);
	void clear();
	void toggleCell(int x, int y);

	int getWidth() const;
	int getHeight() const;

	const std::unordered_set<uint32_t>& getCells() const;

private:
	std::unordered_set<uint32_t> m_cellSet;
	int m_width;
	int m_height;
};