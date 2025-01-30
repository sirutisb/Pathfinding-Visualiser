#include "application.h"
#include <cmath>
#include <imgui.h>
#include <imgui-SFML.h>

const sf::Color Application::BG_COLOR = sf::Color(18, 33, 43);

Application::Application(const sf::Vector2u& size, const std::string& title)
	: window(sf::VideoMode(size), title)
	, gridRenderer(grid, 75.f)
	, camera(window)
	, lastGridPos(-1, -1)
	, leftMouseDown(false)
{
	if (!ImGui::SFML::Init(window)) {
		// error should be handled here
	}
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
}

Application::~Application() {
	ImGui::SFML::Shutdown();
}

void Application::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

// should this be the application's responsibility???
void Application::toggleCell(const sf::Vector2i& mousePos) {
	const sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	const float cellSize = gridRenderer.getCellSize();
	const int gridX = static_cast<int>(std::floor(worldPos.x / cellSize));
	const int gridY = static_cast<int>(std::floor(worldPos.y / cellSize));
	if (gridX < 0 || gridY < 0 || gridX >= grid.getWidth() || gridY >= grid.getHeight()) return;
	if (lastGridPos.x == gridX && lastGridPos.y == gridY) return;
	lastGridPos = {gridX, gridY};
	grid.toggleCell(gridX, gridY);
	gridRenderer.updateCellVertices();
}

void Application::processEvents() {
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
				leftMouseDown = true;
				toggleCell(mousePressed->position);
			}
		} else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouseReleased->button == sf::Mouse::Button::Left) {
				leftMouseDown = false;
				lastGridPos = {-1, -1};
			}
		} else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
			 if (!leftMouseDown) continue;
			 toggleCell(mouseMoved->position);
		}
	}
}

void Application::update() {
	if (menu.isOpen())
		ImGui::SFML::Update(window, clock.restart());
	camera.update();
}

void Application::render() {
	window.clear(Application::BG_COLOR);
	gridRenderer.render(window);
	// animations rendered here? or maybe grid renderer idk yet
	menu.render(window, grid);
	window.display();
}
