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
};