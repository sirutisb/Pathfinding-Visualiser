#pragma once
#include <string>
#include <SFML/Graphics.hpp>
//#include <imgui.h>
//#include <imgui-SFML.h>

#include "grid.h"
#include "gridRenderer.h"
#include "camera.h"
#include "menu.h"


class Application {
public:
	Application(const sf::Vector2u& size, const std::string& title);
	~Application();
	void run();

private:
	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
	sf::View cameraView;
	sf::Clock clock;

	Grid grid;
	GridRenderer gridRenderer;
	Camera camera;
	Menu menu;

	sf::Vector2i mouseToCellPosition(const sf::Vector2i& mousePos) const;
	void setCellState(const sf::Vector2i& pos, bool state);
	void drawLine(const sf::Vector2i& start, const sf::Vector2i& end, bool fillState);

	sf::Vector2i prevGridPos;
	bool leftMouseDown;
	bool fillState;

	static const sf::Color BG_COLOR;
};