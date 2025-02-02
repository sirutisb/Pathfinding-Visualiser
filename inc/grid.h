#pragma once
#include <cstdint>
#include "cell.h"
#include <unordered_set>
#include <string>

class Grid
{
public:
	Grid();
	Grid(int width, int height);

	void resize(int width, int height);
	void clear();
	void toggleCell(int x, int y);
	bool getState(int x, int y) const;
	void setState(int x, int y, bool state);

	int getWidth() const;
	int getHeight() const;

	bool saveToFile(const std::string& fileName);
	bool loadFromFile(const std::string& fileName);

	const std::unordered_set<uint32_t>& getCells() const;

private:
	std::unordered_set<uint32_t> m_cellSet;
	int m_width;
	int m_height;
};