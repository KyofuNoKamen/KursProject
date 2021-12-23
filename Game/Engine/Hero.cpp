#include "../Headers/Hero.h"
#include <iostream>

Hero::Hero(Window* window, Level* level, sf::Image image, std::vector<sf::IntRect> rects, float x, float y, std::string name): Entity(level, image, rects, x, y, squad_counter) {
    isMoving = false;
    this->window = window;
    this->level = level;
    agility = 70;
    damage = 50;
    squad_counter = 4;
    underModificator = false;
    this->x = x;
    this->y = y;

    this->name = name;

    sprite.setOrigin(0, 60);
    
    setAnimationSpeedLimiter(50);
}

void Hero::update(sf::Time deltatime) {
    heroSpriteFunction();
    if (getIsMoving()) {

        makeMicrostep(deltatime);   
        window->checkEnemies();
    }
    else
    {
        heroControl();
        this->x = sprite.getPosition().x;
        this->y = sprite.getPosition().y;
    }
}

void Hero::heroSpriteFunction() {
    sprite.setTextureRect(currentRect);
    window->get_window().draw(sprite);
}

// make hero and enemies move if a movement key was pressed
void Hero::heroControl(){
    window->get_window().setKeyRepeatEnabled(false);

    sf::Vector2f direction;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = DIRECTIONS[0];
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 

        direction = DIRECTIONS[1];

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

        direction = DIRECTIONS[2];
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

        direction = DIRECTIONS[3];
    }
    else {
        return;
    }
    // if the hero starts moving, enemies will do the same
    if (makeStepInDirection(direction)) {
        window->getLevel().StartEnemyMoving();
        //window->checkEnemies();
    }
}

void Hero::set_tile_size(sf::Vector2i tile_size) {
    this->tile_size = tile_size;
}

// !!! íóæíà ëè ýòà ôóíêöèÿ?
void Hero::draw_hero(int x, int y, int width, int height)
{
    sprite.setTextureRect(sf::IntRect(x, y, width, height));
    window->get_window().draw(sprite);
}


