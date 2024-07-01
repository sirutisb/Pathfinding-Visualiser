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
	Grid grid;
	sf::View view = window.getDefaultView();
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
		cameraController.handleEvent(evnt);
		//gridManager.handleEvent(evnt);
		switch (evnt.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyboardEvent(evnt);
			break;
		case sf::Event::KeyReleased:
			handleKeyboardEvent(evnt);
			break;
		case sf::Event::MouseButtonPressed:
			handleMouseEvent(evnt);
		}
	}
}

void Application::handleKeyboardEvent(const sf::Event& evnt)
{
	// TODO: differentiate between keypress and key up
	if (evnt.type == sf::Event::KeyReleased)
		return;

	const sf::Keyboard::Key& keyCode = evnt.key.code;
	if (keyCode == sf::Keyboard::Insert)
		menuData.showMenu = !menuData.showMenu;
	if (keyCode == sf::Keyboard::LShift)
		shift = true;
	if (keyCode == sf::Keyboard::LControl)
		ctrl = true;

}

void Application::handleMouseEvent(const sf::Event& evnt)
{
}

void Application::renderScene()
{
	window.clear(sf::Color(18, 33, 43));
	renderer.render();
	ImGui::SFML::Render(window);
	window.display();
}
