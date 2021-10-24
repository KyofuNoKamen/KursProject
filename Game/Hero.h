#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "Window.h"

class Hero {
public:
    
    Hero(Window* window);
    Hero(Window* window, int, int);
    sf::Sprite heroSprite;
    Window* window;

    void heroSpriteFunction();
    void move(float, float);
private:
    //sf::Rect<int> collider;
    sf::Sprite colliderSprite;
    int speed;
};
