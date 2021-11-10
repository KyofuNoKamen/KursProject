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

    void update(sf::Time);
    void set_tile_size(sf::Vector2i tile_size);
private:
    sf::Vector2i tile_size;
    sf::Texture texture;
    Level* level;
    bool isMoving;

    void heroSpriteFunction();
    void hero_move(sf::Time);
    void draw_hero(int x, int y, int width, int height);
};
