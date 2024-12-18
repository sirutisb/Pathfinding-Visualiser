#include "Application.h"
//#include <imgui.h>
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
	menu.render(window);
	window.display();
}