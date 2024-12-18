#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu();
	void render(sf::RenderWindow& window);
	void toggle();

	bool isOpen() const;
private:
	bool show;

	int gridSize[2];

	int algorithmIndex;
	const char* algorithms[2];

	bool showAnimation;
	float animationDelay;
};