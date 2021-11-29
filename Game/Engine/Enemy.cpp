#include "../Headers/Enemy.h" 
#include <iostream>
//#include "Window.h"

Enemy::Enemy(sf::Image image, Level* level, std::vector<sf::IntRect> rects, float X, float Y, int Agility, int Damage, int Squad_counter/*, SquadVector*/) :Entity(level, image, rects, X, Y, Agility, Damage, Squad_counter) {
	// vremenniy kostyl')
	sprite.setScale(5, 5);
}
