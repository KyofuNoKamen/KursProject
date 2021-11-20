#pragma once
#include "level.h"
#include <SFML/Graphics.hpp>

class Entity {
protected:
	Level* level;
	sf::Clock clock_;
	sf::Vector2f destination;
	sf::Vector2f step;
	sf::IntRect currentRect;
	std::vector<sf::IntRect> spriteRects; // standing, up, right, down, left
	float stepSpeedDivider = 500;
	int animationSpeedLimiter = 100;
	bool isMoving;
public:
	Entity(Level* level, sf::Image image, std::vector<sf::IntRect>, float X, float Y);

	float x, y;
	int health;
	bool life, onGround;

	sf::Texture texture;
	sf::Sprite sprite;

	bool getIsMoving();
	bool makeStepInDirection(sf::Vector2f);
	void makeMicrostep(sf::Time);
	void setAnimationSpeedLimiter(int value);
};