#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
	: m_window{window}
	, m_dragging{false}
	, m_zoomLevel{1.0f}
	, m_view{window.getDefaultView()}
{
}

void Camera::handleEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseWheelScrolled:
	{
		float deltaZoom = ev.mouseWheelScroll.delta < 0 ? 1.1f : 1.0f / 1.1f;
		m_zoomLevel *= deltaZoom;
		m_view.zoom(deltaZoom);
	}
		applyView();
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Right) {
			m_dragging = true;
			lastMousePosition = getMouseWorld();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right)
			m_dragging = false;
		break;
	case sf::Event::Resized:
		m_view.setSize(static_cast<float>(ev.size.width), static_cast<float>(ev.size.height));
		m_view.zoom(m_zoomLevel);
		applyView();
		break;
	default:
		break;
	}
}

void Camera::applyView()
{
	m_window.setView(m_view);
}

void Camera::update()
{
	if (m_dragging) {
		sf::Vector2f currentMousePosition = getMouseWorld();
		sf::Vector2f delta = lastMousePosition - currentMousePosition;
		m_view.move(delta);
		applyView();
		lastMousePosition = getMouseWorld();
	}
}

sf::Vector2f Camera::getMouseWorld()
{
	return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
}
