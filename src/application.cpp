#include "Application.h"
#include "Config.h"

Application::Application(const char* windowName)
	: m_window{sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), windowName}
	, m_grid{0, 0}
	, m_camera{m_window}
	, m_menu{m_grid}
{
	ImGui::SFML::Init(m_window);
	m_window.setFramerateLimit(Config::FPS_LIMIT);
	m_window.setKeyRepeatEnabled(false);
}

void Application::Run()
{
	while (m_window.isOpen()) {
		handleEvents();
		m_camera.update();
		render();
	}
	ImGui::SFML::Shutdown();
}

// Major code cleanup required below....
#include <iostream>
sf::Vector2i getMouseGrid(sf::Vector2i mousePos, sf::RenderWindow& window) {
	//sf::Vector2i mousePos = *reinterpret_cast<sf::Vector2i*>(&ev.mouseMove); // hacky type punning
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	sf::Vector2i clickedGrid{
		static_cast<int>(worldPos.x / Config::NODE_SIZE),
		static_cast<int>(worldPos.y / Config::NODE_SIZE)};
	return clickedGrid;
}

void toggleCell(int x, int y, Grid& grid) {
	std::cout << "Grid Toggled: " << x << "," << y << "\n";
	grid.toggle({ x,y });
}

void Application::handleEvents()
{
	// TODO - check if imgui menu is in context, then ignore the click event
	static bool leftMouse = false;
	static sf::Vector2i lastClickedGrid{-1, -1};
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		if (m_menu.isOpen())
			ImGui::SFML::ProcessEvent(m_window, ev);
		m_camera.handleEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Insert)
				m_menu.toggle();
			break;

		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftMouse = true;
				sf::Vector2i clickedGrid = getMouseGrid(*reinterpret_cast<sf::Vector2i*>(&ev.mouseButton.x), m_window);
				lastClickedGrid = clickedGrid;
				toggleCell(clickedGrid.x, clickedGrid.y, m_grid);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left)
				leftMouse = false;
			break;
		case sf::Event::MouseMoved:
			if (leftMouse) {
				sf::Vector2i clickedGrid = getMouseGrid(*reinterpret_cast<sf::Vector2i*>(&ev.mouseMove), m_window);
				if (clickedGrid != lastClickedGrid) {
					toggleCell(clickedGrid.x, clickedGrid.y, m_grid);
					lastClickedGrid = clickedGrid;
				}
			}
			break;
		default:
			break;
		}
	}
	if (m_menu.isOpen())
		ImGui::SFML::Update(m_window, m_deltaClock.restart());
}


void Application::render()
{
	m_window.clear(sf::Color(18, 33, 43));
	m_grid.render(m_window);
	m_menu.render(m_window);
	m_window.display();
}

