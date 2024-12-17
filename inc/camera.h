#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(sf::RenderWindow& window);
	void handleEvent(sf::Event& ev);
	void update();
private:
	void zoom(float deltaZoom);
	void zoomTest(float deltaZoom);

	sf::Vector2f screenToWorld(int x, int y);

	sf::RenderWindow& window;
	sf::View view;

	bool dragging;
	sf::Vector2f lastMousePosition;
};