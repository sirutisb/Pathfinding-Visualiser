#include "grid.h"
#include <vector>

Grid::Grid() : Grid(0, 0) {}

Grid::Grid(const int width, const int height)
	: m_width(width)
	, m_height(height)
{
}

int Grid::getWidth() const { return m_width; }
int Grid::getHeight() const { return m_height; }

void Grid::clear() { m_cellSet.clear(); }

void Grid::resize(const int width, const int height)
{
	m_width = width;
	m_height = height;

	// remove all cells out of bounds
	std::vector<uint32_t> keys_to_remove;
	for (const auto& key : m_cellSet) {
		const int x = key >> 16;
		const int y = key & 0xFFFF;
		if (x >= m_width || y >= m_height) {
			keys_to_remove.push_back(key);
		}
	}
	for (const auto& key : keys_to_remove) {
		m_cellSet.erase(key);
	}
}

void Grid::toggleCell(const int x, const int y) {
	const uint32_t key = x << 16 | y;
	if (const auto it = m_cellSet.find(key); it != m_cellSet.end()) {
		m_cellSet.erase(it);
	} else {
		m_cellSet.insert(key);
	}
}

const std::unordered_set<uint32_t>& Grid::getCells() const { return m_cellSet; }

