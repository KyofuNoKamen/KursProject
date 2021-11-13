#include "../Headers/Entity.h"

Entity::Entity(Level* level, sf::Image& image, float X, float Y, int W, int H) {
	this->level = level;
	x = X; y = Y; w = W; h = H;
	speed = 0; health = 100; dx = 0; dy = 0;
	life = true; isMoving = false; onGround = true;

	texture.loadFromImage(image);
	sprite.setTexture(texture);
    sprite.setPosition(x, y);
	//sprite.setOrigin(-X, -Y);
}

void Entity::makeMicrostep(sf::Time deltatime) {
    sf::Vector2f microstep = step / stepSpeedDivider * (float)deltatime.asMilliseconds();
    sprite.move(microstep);

    /*if (heroClock.getElapsedTime().asMilliseconds() > animationSpeedLimiter) {
        currentRect.left = (currentRect.left >= 1080) ? 0 : currentRect.left + 120;
        heroClock.restart();
    }*/

    sf::Vector2f distance = destination - sprite.getPosition();
    if (abs(distance.x) <= abs(microstep.x) && abs(distance.y) <= abs(microstep.y)) {
        isMoving = false;
        sprite.setPosition(destination);
    }    
}

// Set destination if no walls at the specified direction
bool Entity::makeStepInDirection(sf::Vector2f direction){
    step = direction;
    destination = sprite.getPosition() + step;

    isMoving = true;
    for (Object obj : level->GetCollidables()) {
        if (obj.rect.contains(destination.x, destination.y)) {
            isMoving = false;
            break;
        }
    }
    return isMoving;
}

bool Entity::getIsMoving() {
    return isMoving;
}

