#include "../Headers/Enemy.h" 
#include <iostream>
//#include "Window.h"

Enemy::Enemy(sf::Image image, Level* level, std::vector<sf::IntRect> rects, float X, float Y) :Entity(level, image, rects, X, Y) {
	// vremenniy kostyl')
	sprite.setScale(5, 5);
}
