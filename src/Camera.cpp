#include "Camera.h"

#include <iostream>

Camera::Camera(sf::RenderTarget& target)
	: target{ target }
	, zoomLevel{ 1.0f }
	, view{ target.getDefaultView() }
{

}

void Camera::handleEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseWheelScrolled:
	{
		float deltaZoom = ev.mouseWheelScroll.delta < 0 ? 1.1f : 1.0f / 1.1f;
		zoomLevel *= deltaZoom;
		view.zoom(deltaZoom);
	}
		applyView();
		std::cout << "Zooming: " << zoomLevel << "\n";
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			dragging = true;
			lastMousePosition = target.mapPixelToCoords(sf::Mouse::getPosition(dynamic_cast<sf::WindowBase&>(target)));
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right)
			dragging = false;
		break;
	case sf::Event::Resized:
		view.setSize(ev.size.width, ev.size.height);
		view.zoom(zoomLevel);
		applyView();
		break;
	default:
		break;
	}
}

void Camera::applyView()
{
	target.setView(view);
}

void Camera::update()
{
	if (dragging) {
		sf::Vector2f currentMousePosition = target.mapPixelToCoords(sf::Mouse::getPosition(dynamic_cast<sf::WindowBase&>(target)));
		sf::Vector2f delta = lastMousePosition - currentMousePosition;
		view.move(delta);
		applyView();
		lastMousePosition = target.mapPixelToCoords(sf::Mouse::getPosition(dynamic_cast<sf::WindowBase&>(target)));
	}
}
