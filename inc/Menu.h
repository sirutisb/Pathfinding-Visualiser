#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include "Grid.h"

struct MenuData
{
	// TODO - save this state in the imgui config?
	sf::Vector2i gridSize{ 8, 8 };
	float nodeSize = 45.0f;
	bool animatePath = false;
	float animationDelay = 0.250f;
};

class Menu {
public:
	Menu(Grid& grid);
	void render(sf::RenderWindow& window);
	bool isOpen() const;
	void toggle();
private:
	Grid& m_grid;
	MenuData menuData;
	bool show;
};