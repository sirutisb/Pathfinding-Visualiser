#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
	Camera(sf::RenderWindow& target);
	void handleEvent(const sf::Event& ev);
	void applyView();
	void update();
private:
	sf::Vector2f getMouseWorld();

	sf::RenderWindow& m_window;
	sf::View m_view;

	float m_zoomLevel;
	bool m_dragging;
	sf::Vector2f lastMousePosition;
};