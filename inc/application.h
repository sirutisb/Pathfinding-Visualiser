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
	Application(int width, int height, const std::string& title);
	void run();

private:
	void processEvents();
	void render();

	sf::RenderWindow window;
	sf::View cameraView;
	sf::Clock clock;

	GridRenderer gridRenderer;
	Grid grid;
	Camera camera;
	Menu menu;
};