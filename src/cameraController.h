#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"

class CameraController {
public:
    CameraController(sf::RenderWindow& window, float zoomFactor = Config::zoomFactor);

    void resize(const sf::Event::SizeEvent& newSize);
    void zoom(float delta);
    void rightClick(bool pressed);
    void update();

private:
    sf::RenderWindow& window;
    sf::View view;
    float zoomLevel;
    float zoomFactor;
    bool isRightClicking;
    sf::Vector2i lastMousePosition;
};