#include "camera.h"

Camera::Camera(sf::RenderWindow& window)
	: window(window)
	, view(window.getDefaultView())
	, dragging(false)
{}

void Camera::handleEvent(sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseWheelScrolled:
		zoomTest(ev.mouseWheelScroll.delta);
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			dragging = true;
			lastMousePosition = screenToWorld(ev.mouseButton.x, ev.mouseButton.y);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			dragging = false;
		}
		break;
	default:
		break;
	}
}

void Camera::update()
{
	if (!dragging) return;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f currentMousePosition = screenToWorld(mousePosition.x, mousePosition.y);
	sf::Vector2f delta = lastMousePosition - currentMousePosition;
	view.move(delta);
	window.setView(view);



	lastMousePosition = screenToWorld(mousePosition.x, mousePosition.y);
}

void Camera::zoom(float deltaScroll)
{
	// TODO: add multiplier constants
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f prevMouseWorld = screenToWorld(mousePosition.x, mousePosition.y);

	float deltaZoom = deltaScroll < 0 ? 1.1f : 1.0f / 1.1f;
	view.zoom(deltaZoom);
	window.setView(view);

	sf::Vector2f mouseWorld = screenToWorld(mousePosition.x, mousePosition.y);
	sf::Vector2f deltaPos = prevMouseWorld - mouseWorld;
	view.move(deltaPos);
	window.setView(view);
}

sf::Vector2f Camera::screenToWorld(int x, int y)
{
	return window.mapPixelToCoords({x, y});
}
