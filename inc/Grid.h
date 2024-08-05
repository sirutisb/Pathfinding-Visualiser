#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Grid {
public:
	Grid(int width, int height);
	void resize(int width, int height);
	void save(const std::string& filename);
	void load(const std::string& filename);
	void clear();
	void render(sf::RenderWindow& window);

	void toggle(sf::Vector2i pos);
private:
	int m_width, m_height;
	std::vector<std::vector<Cell>> cells;
};