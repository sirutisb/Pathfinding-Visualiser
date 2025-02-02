#include "camera.h"
#include <imgui.h>
#include "config.h"

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
	const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	const sf::Vector2f currWorldPos = window.mapPixelToCoords(mousePos);
	const sf::Vector2f delta = prevWorldPos - currWorldPos;
	prevWorldPos = currWorldPos + delta;
	view.move(delta);
	window.setView(view);
}

void Camera::zoom(const float deltaScroll) {
	const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	const sf::Vector2f prevMouseWorld = window.mapPixelToCoords(mousePosition, view);

	// TODO: add multiplier constants
	const float deltaZoom = deltaScroll < 0 ? config::ZOOM_FACTOR : 1.0f / config::ZOOM_FACTOR;
	zoomLevel *= deltaZoom;
	view.zoom(deltaZoom);

	const sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePosition, view);
	const sf::Vector2f deltaPos = prevMouseWorld - mouseWorld;
	view.move(deltaPos);
	window.setView(view);
}

sf::Vector2f Camera::getPosition() const {
	return view.getCenter();
}

sf::View& Camera::getView() { return view; }
