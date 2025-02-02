#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event);
	void update();

	sf::Vector2f getPosition() const;
	sf::View& getView();
private:
	void zoom(float deltaScroll);

	sf::RenderWindow& window;
	sf::View view;

	bool dragging;
	float zoomLevel;
	sf::Vector2f prevWorldPos;
};