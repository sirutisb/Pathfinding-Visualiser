#include "application.h"
#include <cmath>
#include <imgui.h>
#include <imgui-SFML.h>
#include "config.h"

const sf::Color Application::BG_COLOR = sf::Color(18, 33, 43);

Application::Application(const sf::Vector2u& size, const std::string& title)
	: window(sf::VideoMode(size), title)
	, gridRenderer(grid, 75.f)
	, camera(window)
	, prevGridPos(-1, -1) // maybe no longer needed to store invalid position anymore
	, leftMouseDown(false)
{
	if (!ImGui::SFML::Init(window)) {
		// error should be handled here
	}
	window.setFramerateLimit(config::FRAME_RATE);
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

void Application::drawLine(const sf::Vector2i& start, const sf::Vector2i& end, const bool fillState) {
	int dx = abs(end.x - start.x);
	int dy = -abs(end.y - start.y);
	int sx = start.x < end.x ? 1 : -1;
	int sy = start.y < end.y ? 1 : -1;
	int err = dx + dy;

	sf::Vector2i current = start;
	while (true) {
		setCellState(current, fillState);
		if (current.x == end.x && current.y == end.y) break;
		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; current.x += sx; }
		if (e2 <= dx) { err += dx; current.y += sy; }
	}
	gridRenderer.updateCellVertices();
}

void Application::setCellState(const sf::Vector2i& pos, const bool state) {
	const int width = grid.getWidth(), height = grid.getHeight();
	if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height) return;
	grid.setState(pos.x, pos.y, state);
}

sf::Vector2i Application::mouseToCellPosition(const sf::Vector2i& mousePos) const {
	const sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	const float cellSize = gridRenderer.getCellSize();
	const int gridX = static_cast<int>(std::floor(worldPos.x / cellSize));
	const int gridY = static_cast<int>(std::floor(worldPos.y / cellSize));
	return {gridX, gridY};
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
				prevGridPos = mouseToCellPosition(mousePressed->position);
				fillState = !grid.getState(prevGridPos.x, prevGridPos.y);
				setCellState(prevGridPos, fillState);
				gridRenderer.updateCellVertices();
			}
		} else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouseReleased->button == sf::Mouse::Button::Left) {
				leftMouseDown = false;
				//prevGridPos = {-1, -1};
			}
		} else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
			if (!leftMouseDown) continue;
			const sf::Vector2i gridPos = mouseToCellPosition(mouseMoved->position);
			if (gridPos == prevGridPos) continue;
			// currently a small bug where the start of each line tries to fill again over the end of the previous (so each segment end point is filled twice).
			// however with this current implementation of just filling in the cells with the fill state it has no impact on final result.
			drawLine(prevGridPos, gridPos, fillState);
			prevGridPos = gridPos;
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
