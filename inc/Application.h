#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Grid.h"
#include "Camera.h"
#include "Menu.h"

class Application {
public:
	Application(const char* windowName);
	void Run();

private:
	void handleEvents();
	void render();

	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

	Grid m_grid;
	Camera m_camera;
	Menu m_menu;
};