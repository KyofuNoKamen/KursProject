#pragma once
#include "Includes.h"
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
    sf::Texture texture;
    void heroSpriteFunction();
    void hero_move(sf::Time);
    void draw_hero(int x, int y, int width, int height);
/*
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
    int status;
private:
    //sf::Rect<int> collider;
    sf::Sprite colliderSprite;
    int speed;
*/
};
