#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
class Menu
{
public:
	Menu();
	void render(sf::RenderWindow& window, Grid& grid);
	void toggle();

	bool isOpen() const;
private:
	bool show;

	int gridSize[2];

	char fileName[16];

	int algorithmIndex;
	const char* algorithms[2];

	bool showAnimation;
	float animationDelay;
};