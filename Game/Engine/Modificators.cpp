#include "../Headers/Modificators.h"
#include <iostream>
Modificators::Modificators(Level* level, sf::Image image, std::vector<sf::IntRect> rects, float X, float Y) {
    this->level = level;
    spriteRects = rects;
    x = X;
    y = Y;
    isMoving = false; onGround = true;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    currentRect = rects[0];
    sprite.setTextureRect(currentRect);
    sprite.setPosition(x, y);
}