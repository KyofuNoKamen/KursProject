#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Hero::Hero(Window* window) {
    this->window = window;
    speed = 15;
    //collider = sf::Rect<int>(0,100,100,20);
}

Hero::Hero(Window* window, int x, int y):Hero(window) {
    heroSprite.move(x, y);
    colliderSprite.move(x, y + 100);
}

void Hero::heroSpriteFunction() {
    sf::Texture hero;
    if (!hero.loadFromFile("resources/spr.png"))
    {
        std::cout << "Error during loading picture from file/n";
    }
    heroSprite.setTexture(hero);
    heroSprite.setTextureRect(sf::IntRect(198, 34, 96, 128));

    sf::Texture t;
    t.loadFromFile("resources/test.jpg");
    colliderSprite.setTexture(t);

    float x = 0, y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x -= speed;
        heroSprite.setTextureRect(sf::IntRect(535, 341, -96, 134));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x += speed;
        heroSprite.setTextureRect(sf::IntRect(430, 341, 96, 134)); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y -= speed;
        heroSprite.setTextureRect(sf::IntRect(35, 161, 107, 162)); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y += speed;
        heroSprite.setTextureRect(sf::IntRect(166, 215, 134, 99)); 
    }

    // тип collidable - объекты с которыми герой (коллайдер) сталкивается 
    std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
    
    // направление  коллайдера,- то куда герой пытается идти
    sf::Rect<int> colliderDirect = sf::Rect<int>(colliderSprite.getGlobalBounds());
    colliderDirect.left += x;
    colliderDirect.top += y;

    bool canMakeStep = true;
    for (Object obj : collidables) {
        if (colliderDirect.intersects(obj.rect)) {
            canMakeStep = false;
            break;
        }
    }
    // герой передвигается если нету преград
    if (canMakeStep) {
        move(x, y);
    }

    window->get_window().draw(heroSprite);
    window->get_window().draw(colliderSprite);
}

void Hero::move(float x, float y) {
    heroSprite.move(x, y);
    colliderSprite.move(x,y);
    window->moveView(x, y);
}
