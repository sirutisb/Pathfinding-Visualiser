#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
	Camera(sf::RenderTarget& target);
	void handleEvent(const sf::Event& ev);
	void applyView();
	void update();
private:
	sf::RenderTarget& target;
	sf::View view;
	float zoomLevel;

	bool dragging = false;
	sf::Vector2f lastMousePosition;
};