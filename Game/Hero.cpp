#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Hero::Hero(sf::RenderWindow* window) {
    this->window = window;
}

void Hero::heroSpriteFunction() {
    sf::Texture hero;
    if (!hero.loadFromFile("resources/spr.png"))
    {
        std::cout << "Error during loading picture from file/n";
    }
    heroSprite.setTexture(hero);
    heroSprite.setTextureRect(sf::IntRect(198, 34, 96, 128));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        heroSprite.move(-12.0, 0.0); heroSprite.setTextureRect(sf::IntRect(535, 341, -96, 134)); std::cout << "draw hero sprite mov" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { heroSprite.move(12, 0); heroSprite.setTextureRect(sf::IntRect(430, 341, 96, 134)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { heroSprite.move(0, -12); heroSprite.setTextureRect(sf::IntRect(35, 161, 107, 162)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { heroSprite.move(0, 12); heroSprite.setTextureRect(sf::IntRect(166, 215, 134, 99)); }
    window->draw(heroSprite);
}
