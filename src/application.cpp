#include "application.h"
#include "config.h"
#include <imgui-SFML.h>

Application::Application(const char* windowName) :
	window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), windowName),
	renderer(window, grid),
	cameraController(window),
	menuData(renderer.getMenuData())
{
	ImGui::SFML::Init(window);
	ImGui::GetIO().IniFilename = nullptr;
	window.setFramerateLimit(Config::fps);
	window.setKeyRepeatEnabled(false);
}

void Application::run()
{
	while (window.isOpen()) {
		handleEvents();
		ImGui::SFML::Update(window, deltaClock.restart());
		cameraController.update();
		renderScene();
	}
	ImGui::SFML::Shutdown();
}

void Application::handleEvents()
{
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		ImGui::SFML::ProcessEvent(evnt);
		//cameraController.handleEvent(evnt); // todo: maybe handle this in handlemousemove function
		//gridManager.handleEvent(evnt);
		switch (evnt.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			cameraController.resize(evnt.size);
			break;
		case::sf::Event::MouseWheelScrolled:
			cameraController.zoom(evnt.mouseWheelScroll.delta);
			break;
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			handleKeyboardEvent(evnt);
			break;
		case sf::Event::MouseButtonPressed:
		case::sf::Event::MouseButtonReleased:
			handleMouseEvent(evnt);
			break;
		default:
			break;
		}
	}
}

void Application::handleKeyboardEvent(const sf::Event& evnt)
{
	const bool keyPressed = evnt.type == sf::Event::KeyPressed; // otherwise key is released
	const sf::Keyboard::Key& key = evnt.key.code;
	if (keyPressed) {
		if (key == sf::Keyboard::Insert)
			menuData.showMenu = !menuData.showMenu;
	}
	else {
		// handle mouse released
	}

	if (key == sf::Keyboard::LShift)
		shift = keyPressed;
	else if (key == sf::Keyboard::LControl)
		ctrl = keyPressed;
}

void Application::handleMouseEvent(const sf::Event& evnt)
{
	bool pressed = evnt.type == sf::Event::MouseButtonPressed; // otherwise mouse is released
	const sf::Event::MouseButtonEvent& mouse = evnt.mouseButton;
	if (mouse.button == sf::Mouse::Right)
		cameraController.rightClick(pressed);
}

void Application::renderScene()
{
	window.clear(sf::Color(18, 33, 43));
	renderer.render();
	ImGui::SFML::Render(window);
	window.display();
}
