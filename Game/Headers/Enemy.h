#pragma once
#include "Entity.h"
#include <vector>
#include "Level.h"

class Enemy :public Entity {
public:
	Level* level;
	//Window* window;

	Enemy(sf::Image&, Level*, float, float, int, int);
	//Enemy(sf::Image&, sf::String, Level*, float, float, int, int);
	//void enemyMove();
	
};