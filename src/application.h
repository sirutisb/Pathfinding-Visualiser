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
	void handleEvent(const sf::Event& ev);
	void processInput();
	void renderScene();
	// may need functions for dealing with a single instance of a key down event

	sf::RenderWindow window;
	sf::Clock deltaClock;
	Renderer renderer;
	Grid grid;
	CameraController cameraController;
	MenuData& menuData;

	bool m_keyBuffer[sf::Keyboard::KeyCount]{ false };
	bool m_buttonBuffer[sf::Mouse::ButtonCount]{ false };
};