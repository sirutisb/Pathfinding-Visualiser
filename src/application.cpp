#include "Application.h"
//#include <imgui.h>
#include <imgui-SFML.h>

Application::Application(int width, int height, const std::string& title)
	: window(sf::VideoMode(width, height), title)
	, grid()
	, gridRenderer(grid, 75.f)
	, camera(window)
{
	ImGui::SFML::Init(window);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
}

void Application::run()
{
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
	ImGui::SFML::Shutdown();
}

void Application::processEvents()
{
	sf::Event ev;
	while (window.pollEvent(ev)) {
		camera.handleEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Application::update()
{
	camera.update();
}

void Application::render()
{
	window.clear();
	gridRenderer.render(window);

#pragma region testing drawing
	sf::RectangleShape rect({ 200.f, 350.f });
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Cyan);
	window.draw(rect);
#pragma endregion



	// animations rendered here? or maybe grid renderer idk yet
	menu.render();
	window.display();
}