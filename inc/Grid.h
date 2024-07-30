#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Grid {
public:
	Grid(int width, int height);
	void resize(int width, int height);
	//Cell& getCell(int x, int y);
	void render(sf::RenderWindow& window);
private:
	int m_width, m_height;
	std::vector<std::vector<Cell>> cells;
};