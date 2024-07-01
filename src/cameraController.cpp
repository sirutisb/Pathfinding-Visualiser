#include "CameraController.h"

CameraController::CameraController(sf::RenderWindow& window, float zoomFactor)
    : window(window),
    view(window.getDefaultView()), // change to getview
    zoomLevel(1.0f),
    zoomFactor(zoomFactor),
    isRightClicking(false)
{
}

void CameraController::handleEvent(const sf::Event& event)
{
    // unused - (deprecated or wtv u call it)
}

void CameraController::resize(const sf::Event::SizeEvent& newSize)
{
    view.setSize(sf::Vector2f(newSize.width, newSize.height) / zoomLevel);
}

void CameraController::zoom(float delta)
{
    if (delta > 0) zoomLevel *= zoomFactor;
    else if (delta < 0) zoomLevel /= zoomFactor;
    view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y) / zoomLevel); // use defaultview???
}

void CameraController::rightClick(bool pressed)
{
    isRightClicking = pressed;
    if (isRightClicking)
        lastMousePosition = sf::Mouse::getPosition(window);

}

void CameraController::update() {
    if (isRightClicking) {
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f delta = window.mapPixelToCoords(lastMousePosition) - window.mapPixelToCoords(currentMousePosition);
        view.move(delta);
        lastMousePosition = currentMousePosition;
    }
    window.setView(view);
}
