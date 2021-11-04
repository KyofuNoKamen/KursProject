#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "level.h"

class Entity {
private:
	//sf::Vector2i tile_size;
	//Level* level;
public:
	//Window* window;
	//std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
	std::vector<Object> obj; //Вектор всех объектов

	float dx, dy, x, y, speed;
	int w, h, health;
	bool life, isMove, onGround;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;

	sf::FloatRect getRect();
	Entity(sf::Image& image, sf::String Name, float X, float Y, int W, int H);
};