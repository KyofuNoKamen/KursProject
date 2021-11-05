#pragma once
#include "Entity.h"
class Enemy :public Entity {
public:
	Enemy(sf::Image&, sf::String, float, float, int, int);
	void enemyMove(int, std::vector<Object>);
};