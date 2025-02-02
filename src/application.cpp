#include "application.h"
#include <cmath>
#include <imgui.h>
#include <imgui-SFML.h>
#include "config.h"

const sf::Color Application::BG_COLOR = sf::Color(18, 33, 43);

Application* Application::s_Instance = nullptr;

Application& Application::get() {
	return *s_Instance;
}

std::pair<sf::Vector2i, sf::Vector2i> Application::getStartEndPos() const {
	return {startPos, endPos};
}

void Application::setStartEndPos(const sf::Vector2i& start, const sf::Vector2i& end) {
	startPos = start;
	endPos = end;
}

Application::Application(const sf::Vector2u& size, const std::string& title)
	: window(sf::VideoMode(size), title)
	, gridRenderer(grid, 75.f)
	, camera(window)
	, prevGridPos(-1, -1) // maybe no longer needed to store invalid position anymore
	, leftMouseDown(false)
	, debugFont("Fonts/Besty Beige.ttf")
	, debugText(debugFont)
	, startPos(0, 0)
	, endPos(-1, -1)
{
	if (s_Instance) {
		// cannot have another instance. Assert here?
	}
	else {
		Application::s_Instance = this;
	}

	if (!ImGui::SFML::Init(window)) {
		// error should be handled here
	}
	window.setFramerateLimit(config::FRAME_RATE);
	window.setKeyRepeatEnabled(false);

	debugText.setCharacterSize(18);
	debugText.setPosition({ 0.f,0.f });
	debugText.setFillColor(sf::Color::Red);
	debugView.setSize({1920,1080});
	//debugView.setCenter({ 0.f,0.f });
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
	gridRenderer.updateCellVertices(startPos, endPos);
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
			else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift)
				shift = true;
			else if (keyPressed->scancode == sf::Keyboard::Scancode::LControl)
				ctrl = true;
		} else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			if (keyReleased->scancode == sf::Keyboard::Scancode::LShift)
				shift = false;
			else if (keyReleased->scancode == sf::Keyboard::Scancode::LControl)
				ctrl = false;
		} else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				leftMouseDown = true;
				prevGridPos = mouseToCellPosition(mousePressed->position);
				fillState = !grid.getState(prevGridPos.x, prevGridPos.y);
				if (shift) {
					setCellState(prevGridPos, false);
					startPos = prevGridPos;
				} else if (ctrl) {
					setCellState(prevGridPos, false);
					endPos = prevGridPos;
				} else {
					setCellState(prevGridPos, fillState);
				}
				gridRenderer.updateCellVertices(startPos, endPos);
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

void Application::drawStats(sf::RenderWindow& window) {
	std::stringstream ss;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f camPos = camera.getPosition();
	sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePos);
	sf::Vector2i gridPos = mouseToCellPosition(mousePos);
	ss << "Camera: " << camPos.x << ", " << camPos.y << "\n"
	<< "World: " << mouseWorld.x << ", " << mouseWorld.y << "\n"
	<< "Grid: " << gridPos.x << "," << gridPos.y << "\n";
	debugText.setString(ss.str());
	window.setView(debugView);
	window.draw(debugText);
	window.setView(camera.getView());
}


void Application::render() {
	window.clear(Application::BG_COLOR);
	gridRenderer.render(window);
	// animations rendered here? or maybe grid renderer idk yet

	// debug stats
	drawStats(window);

	menu.render(window, grid);
	window.display();
}
