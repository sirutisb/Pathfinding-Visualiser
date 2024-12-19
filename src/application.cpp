#include "application.h"
#include <imgui.h>
#include <imgui-SFML.h>

const sf::Color Application::bgColor = sf::Color(18, 33, 43);

Application::Application(int width, int height, const std::string& title)
	: window(sf::VideoMode(width, height), title)
	, grid()
	, gridRenderer(grid, 75.f)
	, camera(window)
	, menu()
{
	ImGui::SFML::Init(window);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
}

Application::~Application()
{
	ImGui::SFML::Shutdown();
}

void Application::run()
{
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Application::processEvents()
{
	sf::Event ev;
	while (window.pollEvent(ev)) {
		if (menu.isOpen())
			ImGui::SFML::ProcessEvent(window, ev);
		camera.handleEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Insert)
				menu.toggle();
			break;
		case sf::Event::MouseButtonPressed:
			if (ImGui::GetIO().WantCaptureMouse) break;
			if (ev.mouseButton.button == sf::Mouse::Left) {
				//sf::Vector2f worldPos = window.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
				//int row = static_cast<int>(worldPos.y / cellSize);
				//int col = static_cast<int>(worldPos.x / cellSize);
				//grid.toggleCellState(row, col);
			}
			break;
		default:
			break;
		}
	}
}

void Application::update()
{
	if (menu.isOpen())
		ImGui::SFML::Update(window, clock.restart());
	camera.update();
}

void Application::render()
{
	window.clear(Application::bgColor);
	gridRenderer.render(window);
	// animations rendered here? or maybe grid renderer idk yet
	menu.render(window, grid);
	window.display();
}