#include "CameraController.h"

CameraController::CameraController(sf::RenderWindow& window, float zoomFactor)
    : window(window),
    view(window.getDefaultView()), // change to getview
    zoomLevel(1.0f),
    zoomFactor(zoomFactor),
    isRightClicking(false) {
    //window.setView(view); // maybe comment out
}

void CameraController::handleEvent(const sf::Event& event) {
    switch (event.type) {
    case sf::Event::Resized:
        view.setSize(sf::Vector2f(event.size.width, event.size.height) / zoomLevel);
        break;
    case sf::Event::MouseWheelScrolled:
        if (event.mouseWheelScroll.delta > 0) zoomLevel *= zoomFactor;
        else if (event.mouseWheelScroll.delta < 0) zoomLevel /= zoomFactor;
        view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y) / zoomLevel); // use defaultview???
        break;
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Button::Right) {
            isRightClicking = true;
            lastMousePosition = sf::Mouse::getPosition(window);
        }
        break;
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Button::Right) isRightClicking = false;
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Z) {
            zoomLevel *= zoomFactor;
            view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y) / zoomLevel);
        }
        else if (event.key.code == sf::Keyboard::X) {
            zoomLevel /= zoomFactor;
            view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y) / zoomLevel);
        }
        break;
    }
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
