#pragma once
#include <string>
#include <SFML/Graphics.hpp>
//#include <imgui.h>
//#include <imgui-SFML.h>
//
//#include "Grid.h"
//#include "Camera.h"
//#include "Menu.h"

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

	//Grid grid;
};