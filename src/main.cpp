#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
//#include "utils.h"

constexpr uint32_t WINDOW_WIDTH  = 1080;
constexpr uint32_t WINDOW_HEIGHT = 1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinder Visualiser");
	ImGui::SFML::Init(window);
	ImGui::GetIO().IniFilename = nullptr;
	Renderer renderer(window);
	//sf::View view({ 0.0f, 0.0f }, { WINDOW_WIDTH, WINDOW_HEIGHT});
	sf::View view = window.getDefaultView(); // maybe better since our origin is now top left of our window
	sf::CircleShape circle(400,64);
	circle.setFillColor(sf::Color(204, 77, 5));
	circle.setOrigin(400, 400);
	window.setView(view);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock deltaClock;
	MenuData& menuData = renderer.getMenuData();

	float zoomLevel = 1.0f;
	constexpr float zoomFactor = 1.1f;

	bool isRightClicking = false;
	sf::Vector2i lastMousePosition;
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			ImGui::SFML::ProcessEvent(evnt);
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Insert)
					menuData.showMenu = !menuData.showMenu;
				else if (evnt.key.code == sf::Keyboard::Z) {
					zoomLevel *= zoomFactor;
					sf::Vector2u windowSize = window.getSize();
					view.setSize(windowSize.x / zoomLevel, windowSize.y / zoomLevel);
				}
				else if (evnt.key.code == sf::Keyboard::X) {
					zoomLevel /= zoomFactor;
					sf::Vector2u windowSize = window.getSize();
					view.setSize(windowSize.x / zoomLevel, windowSize.y / zoomLevel);
				}
				break;
			case sf::Event::MouseWheelScrolled:
				if (evnt.mouseWheelScroll.delta > 0)
					zoomLevel *= zoomFactor;
				else if (evnt.mouseWheelScroll.delta < 0)
					zoomLevel /= zoomFactor;
				{
					const auto& size = window.getSize();
					view.setSize(sf::Vector2f(size.x, size.y) / zoomLevel);
				}
				break;
			case::sf::Event::MouseButtonPressed:
				if (evnt.mouseButton.button == sf::Mouse::Button::Right) {
						isRightClicking = true;
						lastMousePosition = sf::Mouse::getPosition(window);
				}
				break;
			case::sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Button::Right)
					isRightClicking = false;
				break;
			case sf::Event::Resized:
				const auto& size = evnt.size;
				view.setSize(sf::Vector2f(size.width, size.height) / zoomLevel);
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		// Physical world logic here
		if (isRightClicking) {
			sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f delta = window.mapPixelToCoords(lastMousePosition) - window.mapPixelToCoords(currentMousePosition);
			view.move(delta);
			lastMousePosition = currentMousePosition;
		}


		window.clear(sf::Color(18, 33, 43));
		window.setView(view);
		window.draw(circle);
		renderer.render();
		renderer.renderMenu();
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}