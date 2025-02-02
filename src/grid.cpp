#include "grid.h"
#include <string>
#include <fstream>
#include "application.h"

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
	std::ofstream file(fileName, std::ios::binary);
	if (!file) return false;

	file.write(reinterpret_cast<const char*>(&m_width), sizeof(m_width));
	file.write(reinterpret_cast<const char*>(&m_height), sizeof(m_height));

	auto [startPos, endPos] = Application::get().getStartEndPos();
	const uint32_t startKey = startPos.x << 16 | startPos.y;
	const uint32_t endKey = endPos.x << 16 | endPos.y;
	file.write(reinterpret_cast<const char*>(&startKey), sizeof(startKey));
	file.write(reinterpret_cast<const char*>(&endKey), sizeof(endKey));

	int numObstacles = m_cellSet.size();
	file.write(reinterpret_cast<const char*>(&numObstacles), sizeof(numObstacles));
	for (const auto& key : m_cellSet) {
		file.write(reinterpret_cast<const char*>(&key), sizeof(key));
	}
	return file.good();
}

bool Grid::loadFromFile(const std::string& fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file) return false;

	int32_t width, height;
	file.read(reinterpret_cast<char*>(&width), sizeof(width));
	file.read(reinterpret_cast<char*>(&height), sizeof(height));
	resize(width, height);

	// Start/End positions
	int32_t startKey, endKey;
	file.read(reinterpret_cast<char*>(&startKey), sizeof(startKey));
	file.read(reinterpret_cast<char*>(&endKey), sizeof(endKey));

	sf::Vector2i startPos{ startKey >> 16, startKey & 0xFFFF };
	sf::Vector2i endPos{endKey >> 16, endKey & 0xFFFF};
	Application::get().setStartEndPos(startPos, endPos);

	uint32_t numObstacles;
	file.read(reinterpret_cast<char*>(&numObstacles), sizeof(numObstacles));

	clear();
	for (int i = 0; i < numObstacles; i++) {
		uint32_t key;
		file.read(reinterpret_cast<char*>(&key), sizeof(key));
		m_cellSet.insert(key);
	}

	return file.good();
}

const std::unordered_set<uint32_t>& Grid::getCells() const { return m_cellSet; }

