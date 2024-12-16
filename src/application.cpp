#include "Application.h"
//#include <imgui.h>
#include <imgui-SFML.h>

Application::Application(int width, int height, const std::string& title)
	: window(sf::VideoMode(width, height), title)
	, grid()
	, gridRenderer(grid, 75.f)
{
	ImGui::SFML::Init(window);
	window.setFramerateLimit(20);
	window.setKeyRepeatEnabled(false);
}

void Application::run()
{
	while (window.isOpen()) {
		processEvents();
		render();
	}
	ImGui::SFML::Shutdown();
}

void Application::processEvents()
{
	sf::Event ev;
	while (window.pollEvent(ev)) {
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


void Application::render()
{
	window.clear();
	gridRenderer.render(window);
	// animations rendered here? or maybe grid renderer idk yet
	menu.render();
	window.display();
}