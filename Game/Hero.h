#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
public:
    
    Hero(sf::RenderWindow* window);
    sf::Sprite heroSprite;
    sf::RenderWindow* window;

    void heroSpriteFunction();
    void hero_move();
    void set_tile_size(sf::Vector2i tile_size);
    void draw_hero(int x, int y, int width, int height);
private:
    sf::Vector2i tile_size;
};
