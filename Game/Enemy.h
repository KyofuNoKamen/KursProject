#pragma once
#include "Entity.h"
class Enemy :public Entity {
public:
	Enemy(sf::Image& image, sf::String Name, float X, float Y, int W, int H);
};