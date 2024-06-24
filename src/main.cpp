#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
//#include "utils.h"
#include "cameraController.h"

constexpr uint32_t WINDOW_WIDTH  = 1080;
constexpr uint32_t WINDOW_HEIGHT = 1080;

void handleEvents(sf::RenderWindow& window, CameraController& cameraController, MenuData& menuData) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		ImGui::SFML::ProcessEvent(evnt);
		cameraController.handleEvent(evnt);
		switch (evnt.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (evnt.key.code == sf::Keyboard::Insert)
				menuData.showMenu = !menuData.showMenu;
			break;
		}
	}
}

void renderScene(sf::RenderWindow& window, Renderer& renderer, sf::CircleShape& circle) {
	window.clear(sf::Color(18, 33, 43));
	//window.draw(circle);
	renderer.render();
	ImGui::SFML::Render(window);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinder Visualiser");
	ImGui::SFML::Init(window);
	ImGui::GetIO().IniFilename = nullptr;
	Grid grid({16, 16}, 65.0f);
	Renderer renderer(window, grid);
	//sf::View view({ 0.0f, 0.0f }, { WINDOW_WIDTH, WINDOW_HEIGHT});
	sf::View view = window.getDefaultView(); // maybe better since our origin is now top left of our window
	window.setView(view);
	sf::CircleShape circle(400, 64);
	circle.setFillColor(sf::Color(204, 77, 5));
	circle.setOrigin(400, 400);
	window.setFramerateLimit(30);
	window.setKeyRepeatEnabled(false);

	sf::Clock deltaClock;
	MenuData& menuData = renderer.getMenuData();
	CameraController cameraController(window);
	while (window.isOpen()) {
		handleEvents(window, cameraController, menuData);
		ImGui::SFML::Update(window, deltaClock.restart());
		cameraController.update();
		renderScene(window, renderer, circle);
	}
	ImGui::SFML::Shutdown();
	return 0;
}