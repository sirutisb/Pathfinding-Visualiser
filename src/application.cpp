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
		processInput();
		ImGui::SFML::Update(window, deltaClock.restart());

		//printf("RightClick: %s\n", m_buttonBuffer[sf::Mouse::Right] ? "true" : "false");
		cameraController.update();
		renderScene();
	}
	ImGui::SFML::Shutdown();
}

void Application::handleEvents()
{
	sf::Event ev;
	while (window.pollEvent(ev)) {
		ImGui::SFML::ProcessEvent(ev);
		handleEvent(ev);
		//gridManager.handleEvent(evnt);
	}
}

//void Application::handleKeyboardEvent(const sf::Event& evnt)
//{
//	const bool keyPressed = evnt.type == sf::Event::KeyPressed; // otherwise key is released
//	const sf::Keyboard::Key& key = evnt.key.code;
//	if (keyPressed) {
//		if (key == sf::Keyboard::Insert)
//			menuData.showMenu = !menuData.showMenu;
//	}
//	else {
//		// handle mouse released
//	}
//
//	if (key == sf::Keyboard::LShift)
//		shift = keyPressed;
//	else if (key == sf::Keyboard::LControl)
//		ctrl = keyPressed;
//}


void Application::handleEvent(const sf::Event& ev)
{
	switch (ev.type) {
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::Resized:
		cameraController.resize(ev.size);
		break;
	case sf::Event::MouseWheelScrolled:
		cameraController.zoom(ev.mouseWheelScroll.delta);
		break;
	case sf::Event::KeyPressed:
		m_keyBuffer[ev.key.code] = true;
		if (ev.key.code == sf::Keyboard::Insert)
			menuData.showMenu = !menuData.showMenu;
		break;
	case sf::Event::KeyReleased:
		m_keyBuffer[ev.key.code] = false;
		break;
	case sf::Event::MouseButtonPressed:
		m_buttonBuffer[ev.mouseButton.button] = true;
		break;
	case sf::Event::MouseButtonReleased:
		m_buttonBuffer[ev.mouseButton.button] = false;
		break;
	default:
		break;
	}

	/*switch (evnt.type) {
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
	}*/
}

void Application::processInput()
{
	cameraController.rightClick(m_buttonBuffer[sf::Mouse::Right]);
}

void Application::renderScene()
{
	window.clear(sf::Color(18, 33, 43));
	renderer.render();
	ImGui::SFML::Render(window);
	window.display();
}
