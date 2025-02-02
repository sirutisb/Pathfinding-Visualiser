#pragma once
#include <string>
#include <SFML/Graphics.hpp>
//#include <imgui.h>
//#include <imgui-SFML.h>

#include <stdbool.h>
#include <stdbool.h>

#include "grid.h"
#include "gridRenderer.h"
#include "camera.h"
#include "menu.h"

class Application {
public:
	Application(const sf::Vector2u& size, const std::string& title);
	~Application();
	void run();

	static Application& get();
	std::pair<sf::Vector2i, sf::Vector2i> getStartEndPos() const;
	void setStartEndPos(const sf::Vector2i& start, const sf::Vector2i& end);

private:
	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
	sf::Clock clock;

	Grid grid;
	GridRenderer gridRenderer;
	Camera camera;
	Menu menu;

	sf::Vector2i mouseToCellPosition(const sf::Vector2i& mousePos) const;
	void setCellState(const sf::Vector2i& pos, bool state);
	void drawLine(const sf::Vector2i& start, const sf::Vector2i& end, bool fillState);

	// debug info
	sf::Font debugFont;
	sf::Text debugText;
	sf::View debugView;


	bool shift = false;
	bool ctrl = false;
	sf::Vector2i startPos;
	sf::Vector2i endPos;

	void drawStats(sf::RenderWindow& window);

	sf::Vector2i prevGridPos;
	bool leftMouseDown;
	bool fillState;

	static const sf::Color BG_COLOR;
	
	static Application* s_Instance;
};