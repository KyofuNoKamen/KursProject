#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
public:
    
    Hero(sf::RenderWindow* window);
    sf::Sprite heroSprite;
    sf::RenderWindow* window;

    void heroSpriteFunction();
private:
   

};
