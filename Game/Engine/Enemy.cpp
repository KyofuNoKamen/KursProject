#include "../Headers/Enemy.h" 
#include <iostream>
//#include "Window.h"

Enemy::Enemy(sf::Image image, Level* level, std::vector<sf::IntRect> rects, float X, float Y, int Chance) :Entity(level, image, rects, X, Y, Chance) {
	// vremenniy kostyl')
	sprite.setScale(5, 5);
}
