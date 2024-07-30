#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include "Grid.h"

struct MenuData
{
	sf::Vector2i gridSize{ 8, 8 };
	float nodeSize = 45.0f;
	bool animatePath = false;
	float animationDelay = 0.250f;
};

class MenuManager {
public:
	MenuManager(Grid& grid);
	void render(sf::RenderWindow& window);
	bool isOpen();
	void toggle();
private:
	Grid& m_grid;
	MenuData menuData;
	bool show;
};