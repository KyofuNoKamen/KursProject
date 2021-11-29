#pragma once
#include "Entity.h"
#include <vector>

class Enemy :public Entity {
public:
	Enemy(sf::Image, Level*, std::vector<sf::IntRect>, float, float, int, int, int/*, SquadVector*/);
};