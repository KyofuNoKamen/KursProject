#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
public:
    void heroSpriteFunction();
    Hero(sf::RenderWindow* window);
    sf::Sprite heroSprite;
    sf::RenderWindow* window;
private:
    
};
