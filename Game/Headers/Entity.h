#pragma once
//#include "level.h"
#include <SFML/Graphics.hpp>

class Entity {
private:

public:
	float dx, dy, x, y, speed;
	int w, h, health;
	bool life, isMove, onGround;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	//Level* level;

	sf::FloatRect getRect();
	Entity(sf::Image& image, sf::String Name, float X, float Y, int W, int H);
};