#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "grid.h"
#include "pathfinder.h"
#include <imgui.h>

struct MenuData
{
	bool showMenu = true;
	Vec2i gridSize = { 16,16 };
	float nodeSize = 50.0f;
	bool animatePath = false;
	float animationDelay = 0.1f;
};

class Renderer
{
public:
	Renderer(sf::RenderTarget& target, Grid& grid);
	~Renderer();
	void render();
	void renderMenu();
	MenuData& getMenuData();
	sf::VertexArray createGridVertex(const sf::Vector2i& gridSize, float cellSize);

private:
	void renderGrid();

	sf::RenderTarget& m_target;
	MenuData m_menuData;
	Grid& m_grid;
	sf::VertexArray m_gridVertex;
	Pathfinder* m_pathfinder;
};