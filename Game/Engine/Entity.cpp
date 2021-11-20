#include "../Headers/Entity.h"

Entity::Entity(Level* level, sf::Image image, std::vector<sf::IntRect> rects, float x, float y) {
	this->level = level;
    spriteRects = rects;
    health = 100;
	life = true; isMoving = false; onGround = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
    currentRect = rects[0];
    sprite.setTextureRect(currentRect);
    sprite.setPosition(x, y);
	//sprite.setOrigin(-X, -Y);
}

// entity makes microstep towards destination
void Entity::makeMicrostep(sf::Time deltatime) {
    sf::Vector2f microstep = step / stepSpeedDivider * (float)deltatime.asMilliseconds();
    sprite.move(microstep);

    // movement animation
    if (clock_.getElapsedTime().asMilliseconds() > animationSpeedLimiter) {
        currentRect.left = (currentRect.left >= texture.getSize().x - spriteRects[0].width) ? 0 : currentRect.left + spriteRects[0].width;
        sprite.setTextureRect(currentRect);
        clock_.restart();
        
    }

    // if entity at (or near) destination point then set position directly at destination and stop movement
    // this also ensure that entity wont pass by the destination
    sf::Vector2f distance = destination - sprite.getPosition();
    if (abs(distance.x) <= abs(microstep.x) && abs(distance.y) <= abs(microstep.y)) {
        isMoving = false;
        sprite.setPosition(destination);
        currentRect = spriteRects[0];
        //currentRect.left = 0;
        sprite.setTextureRect(currentRect);
    }    
}

// Set destination if no walls at the specified direction
bool Entity::makeStepInDirection(sf::Vector2f direction){
    step = direction * (float) level->GetTileSize().x;
    destination = sprite.getPosition() + step;
    isMoving = true;
    for (Object obj : level->GetCollidables()) {
        if (obj.rect.contains(destination.x, destination.y)) {
            isMoving = false;
            break;
        }
    }

    // if no obstacle ahead then we choose spriteRect depend on direction
    if (isMoving) {
        if (direction == DIRECTIONS[0]) currentRect = spriteRects[1];       // UP
        else if (direction == DIRECTIONS[1]) currentRect = spriteRects[2];  // RIGHT
        else if (direction == DIRECTIONS[2]) currentRect = spriteRects[3];  // DOWN
        else if (direction == DIRECTIONS[3]) currentRect = spriteRects[4];  // LEFT
    }

    clock_.restart();
    return isMoving;
}

void Entity::setAnimationSpeedLimiter(int value) {
    animationSpeedLimiter = value;
}

bool Entity::getIsMoving() {
    return isMoving;
}

