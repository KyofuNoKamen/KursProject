#pragma once
#include "level.h"
#include <SFML/Graphics.hpp>

class Modificators {
protected:
	Level* level;
	sf::Clock clock_;
	sf::Vector2f destination;
	sf::Vector2f step;
	sf::IntRect currentRect;
	std::vector<sf::IntRect> spriteRects; // standing, up, right, down, left
	//std::vector<Entity> squad_vector;
	float stepSpeedDivider = 500;
	int animationSpeedLimiter = 100;
	bool isMoving;
public:
	Modificators(Level* level, sf::Image image, std::vector<sf::IntRect>, float X, float Y);

	float x, y;
	int damage;
	std::string name;
	int modificator_range;
	bool onGround;
	bool underModificator;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture get_texture();
	bool getIsMoving();
	bool makeStepInDirection(sf::Vector2f);
	void makeMicrostep(sf::Time);
	void setAnimationSpeedLimiter(int value);
};