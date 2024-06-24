#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
//#include "utils.h"

constexpr uint32_t WINDOW_WIDTH  = 1080;
constexpr uint32_t WINDOW_HEIGHT = 1080;

struct KeyInfo
{
	bool leftMouse{};
	bool rightMouse{};
};

KeyInfo keyInfo;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinder Visualiser");
	ImGui::SFML::Init(window);
	ImGui::GetIO().IniFilename = nullptr;
	Renderer renderer(window);
	sf::View view({ 0.0f, 0.0f }, { WINDOW_WIDTH, WINDOW_HEIGHT});
	sf::CircleShape circle(400,64);
	circle.setFillColor(sf::Color(204, 77, 5));
	circle.setOrigin(400, 400);
	window.setView(view);
	window.setFramerateLimit(30);
	window.setKeyRepeatEnabled(false);

	sf::Clock deltaClock;
	MenuData& menuData = renderer.getMenuData();
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
				break;
			case::sf::Event::MouseButtonPressed:
				const auto& button = evnt.mouseButton.button;
				if (button == sf::Mouse::Button::Left)
					keyInfo.leftMouse = true;
			case sf::Event::Resized:
				const auto& size = evnt.size;
				view.setSize(sf::Vector2f(size.width, size.height));
				window.setView(view);
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		window.clear(sf::Color(18, 33, 43));
		window.draw(circle);
		renderer.render();
		renderer.renderMenu();
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}