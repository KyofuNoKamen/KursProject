#pragma once
#include "../Headers/Window.h"
#include "../Headers/Level.h"

class Hero: public Entity{
public:
    Hero(Window* window, Level* level, sf::Image image, std::vector<sf::IntRect> rects, float x, float y);
    Window* window;

    void update(sf::Time);
    void set_tile_size(sf::Vector2i tile_size);
private:
    sf::Vector2i tile_size;
    Level* level;
    bool isMoving;
    void heroSpriteFunction();
    void heroControl();
    void draw_hero(int x, int y, int width, int height);

};
