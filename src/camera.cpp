#include "camera.h"
#include <imgui.h>

Camera::Camera(sf::RenderWindow& window)
	: window(window)
	, view(window.getDefaultView())
	, dragging(false)
	, zoomLevel(1.0f)
{
}

void Camera::handleEvent(const sf::Event& event) {
	if (const auto* mouseScroll = event.getIf<sf::Event::MouseWheelScrolled>()) {
		zoom(mouseScroll->delta);
	} else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePressed->button == sf::Mouse::Button::Right) {
			prevWorldPos = window.mapPixelToCoords(mousePressed->position);
			dragging = true;
		}
	} else if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
		if (mouseReleased->button == sf::Mouse::Button::Right) {
			dragging = false;
		}
	} else if (const auto* windowResized = event.getIf<sf::Event::Resized>()) {
		view.setSize(static_cast<sf::Vector2f>(windowResized->size));
		view.zoom(zoomLevel);
		window.setView(view);
	}
}

void Camera::update() {
	if (!dragging) return;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f currWorldPos = window.mapPixelToCoords(mousePos);
	sf::Vector2f delta = prevWorldPos - currWorldPos;
	prevWorldPos = currWorldPos + delta;
	view.move(delta);
	window.setView(view);
}

void Camera::zoom(float deltaScroll) {
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
