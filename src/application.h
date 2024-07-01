#pragma once
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "cameraController.h"

class Application
{
public:
	Application(const char* windowName);
	void run();

private:
	void handleEvents();
	void handleKeyboardEvent(const sf::Event& evnt);
	void handleMouseEvent(const sf::Event& evnt);
	void renderScene();

	sf::RenderWindow window;
	sf::Clock deltaClock;
	Renderer renderer;
	Grid grid;
	CameraController cameraController;
	MenuData& menuData;

	bool shift = false, ctrl = false;
};