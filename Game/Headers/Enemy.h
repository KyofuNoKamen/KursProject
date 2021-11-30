#pragma once
#include "Entity.h"
#include <vector>

class Enemy :public Entity {
public:
	Enemy(sf::Image, Level*, std::vector<sf::IntRect>, float, float, int/*, SquadVector*/);
	std::vector<Enemy> squad_vector;
	//float coordinates_x;
	//float coordinates_y;
};