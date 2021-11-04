#include "Entity.h"

Entity::Entity(sf::Image& image, sf::String Name, float X, float Y, int W, int H) {
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0; health = 100; dx = 0; dy = 0;
	life = true; isMove = false;

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(0, 0);
}