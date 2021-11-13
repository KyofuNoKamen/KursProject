#pragma once
#include "level.h"
#include <SFML/Graphics.hpp>

class Entity {
private:
	Level* level;
	sf::Vector2f destination;
	sf::Vector2f step;
	float stepSpeedDivider = 350;
	int animationSpeedLimiter = 60;
	bool isMoving;
public:
	float dx, dy, x, y, speed;
	int w, h, health;
	bool life, onGround;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::FloatRect getRect();
	bool getIsMoving();
	bool makeStepInDirection(sf::Vector2f);
	void makeMicrostep(sf::Time);
	Entity(Level* level, sf::Image& image, float X, float Y, int W, int H);
};