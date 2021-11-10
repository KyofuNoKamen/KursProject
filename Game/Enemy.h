#pragma once
#include "Entity.h"
//#include "Window.h"
#include "Level.h"

class Enemy :public Entity {
public:
	Level* level;
	//Window* window;

	Enemy(sf::Image&, sf::String, Level*, float, float, int, int);
	//Enemy(sf::Image&, sf::String, Level*, float, float, int, int);
	void enemyMove(int, std::vector<Object>);
	
};