#pragma once
#include <SFML/Graphics.hpp>

class CameraController {
public:
    CameraController(sf::RenderWindow& window, float zoomFactor = 1.1f);

    void handleEvent(const sf::Event& event);
    void update();
    void applyView();

private:
    sf::RenderWindow& window;
    sf::View view;
    float zoomLevel;
    float zoomFactor;
    bool isRightClicking;
    sf::Vector2i lastMousePosition;
};