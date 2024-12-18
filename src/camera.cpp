#include "camera.h"

Camera::Camera(sf::RenderWindow& window)
	: window(window)
	, view(window.getDefaultView())
	, dragging(false)
	, zoomLevel(1.0f)
{
}

void Camera::handleEvent(sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseWheelScrolled:
		zoom(ev.mouseWheelScroll.delta);
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			prevWorldPos = window.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
			dragging = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			dragging = false;
		}
		view.getSize();
		break;
	case sf::Event::Resized:
		view.setSize(static_cast<float>(ev.size.width), static_cast<float>(ev.size.height));
		view.zoom(zoomLevel);
		window.setView(view);
		break;
	default:
		break;
	}
}

void Camera::update()
{
	if (!dragging) return;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f currWorldPos = window.mapPixelToCoords(mousePos);
	sf::Vector2f delta = prevWorldPos - currWorldPos;
	prevWorldPos = currWorldPos + delta;
	view.move(delta);
	window.setView(view);
}

void Camera::zoom(float deltaScroll)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f prevMouseWorld = window.mapPixelToCoords(mousePosition, view);

	// TODO: add multiplier constants
	float deltaZoom = deltaScroll < 0 ? 1.1f : 1.0f / 1.1f;
	zoomLevel *= deltaZoom;
	view.zoom(deltaZoom);

	sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePosition, view);
	sf::Vector2f deltaPos = prevMouseWorld - mouseWorld;
	view.move(deltaPos);
	window.setView(view);
}