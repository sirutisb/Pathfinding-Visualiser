#include "Application.h"
//#include <imgui.h>
#include <imgui-SFML.h>

Application::Application(int width, int height, const std::string& title)
	: window(sf::VideoMode(width, height), title)
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
	sf::RectangleShape rec({ 50, 150 });
	rec.setPosition({ 800, 800 });
	window.draw(rec);
	// render grid
	// render menu
	window.display();
}