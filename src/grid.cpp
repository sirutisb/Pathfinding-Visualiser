#include "grid.h"
#include <string>
#include <fstream>
#include "application.h"
#include "gridFile.h"

Grid::Grid() : Grid(0, 0) {}

Grid::Grid(const int width, const int height)
	: m_width(width)
	, m_height(height)
{
}

int Grid::getWidth() const { return m_width; }
int Grid::getHeight() const { return m_height; }

void Grid::clear() { m_cellSet.clear(); }

void Grid::resize(const int width, const int height) {
	m_width = width;
	m_height = height;

	// remove all cells out of bounds
	std::erase_if(m_cellSet, [this](const auto& key) {
		const int x = key >> 16;
		const int y = key & 0xFFFF;
		return x >= m_width || y >= m_height;
	});
}

void Grid::toggleCell(const int x, const int y) {
	const uint32_t key = x << 16 | y;
	if (const auto it = m_cellSet.find(key); it != m_cellSet.end()) {
		m_cellSet.erase(it);
	} else {
		m_cellSet.insert(key);
	}
}

bool Grid::getState(const int x, const int y) const {
	const uint32_t key = x << 16 | y;
	return m_cellSet.contains(key);
}

void Grid::setState(const int x, const int y, const bool state) {
	const uint32_t key = x << 16 | y;
	if (state) {
		m_cellSet.insert(key);
	} else {
		m_cellSet.erase(key);
	}
}

bool Grid::saveToFile(const std::string& fileName) {
	GridFile gridFile(*this);
	return gridFile.save(fileName);
}

bool Grid::loadFromFile(const std::string& fileName) {
	GridFile gridFile(*this);
	return gridFile.load(fileName);
}

const std::unordered_set<uint32_t>& Grid::getCells() const { return m_cellSet; }

