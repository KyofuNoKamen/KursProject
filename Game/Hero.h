#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Level.h"

class Hero {
public:
    
    Hero(Window* window);
    Hero(Window* window, int x, int y);
    sf::Sprite heroSprite;
    Window* window;

    void heroSpriteFunction();
    void hero_move();
    void set_tile_size(sf::Vector2i tile_size);
    void draw_hero(int x, int y, int width, int height);
private:
    sf::Vector2i tile_size;
    Level* level;
};
