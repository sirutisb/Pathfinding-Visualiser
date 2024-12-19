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

	sf::RenderWindow& window;
	sf::View view;

	bool dragging;
	float zoomLevel;
	sf::Vector2f prevWorldPos;
};