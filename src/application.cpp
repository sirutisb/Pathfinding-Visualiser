#include "application.h"
#include <imgui.h>
#include <imgui-SFML.h>

const sf::Color Application::bgColor = sf::Color(18, 33, 43);

Application::Application(const sf::Vector2u& size, const std::string& title)
	: window(sf::VideoMode(size), title)
	, grid()
	, gridRenderer(grid, 75.f)
	, camera(window)
	, menu()
{
	bool init = ImGui::SFML::Init(window);
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
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		if (menu.isOpen())
			ImGui::SFML::ProcessEvent(window, *event);
		camera.handleEvent(*event);

		if (event->is<sf::Event::Closed>()) {
			window.close();
		} else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				window.close();
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Insert)
				menu.toggle();
		} else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				// stuff
			}
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
