#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

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
    draw_hero(198, 34, 96, 128);
    
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        heroSprite.move(-tile_size.x, 0.0); heroSprite.setTextureRect(sf::IntRect(535, 341, -96, 134)); std::cout << "draw hero sprite mov" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { heroSprite.move(tile_size.x, 0); heroSprite.setTextureRect(sf::IntRect(430, 341, 96, 134)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { heroSprite.move(0, -tile_size.y); heroSprite.setTextureRect(sf::IntRect(35, 161, 107, 162)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { heroSprite.move(0, tile_size.y); heroSprite.setTextureRect(sf::IntRect(166, 215, 134, 99)); }
    */
    //window->draw(heroSprite);
}

void Hero::hero_move()
{
    window->setKeyRepeatEnabled(false);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        heroSprite.move(sf::Vector2f (-tile_size.x, 0.0)); draw_hero(535, 341, -96, 134); std::cout << "draw hero sprite mov" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { heroSprite.move(tile_size.x, 0); draw_hero(430, 341, 96, 134); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { heroSprite.move(0, -tile_size.y); draw_hero(35, 161, 107, 162); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { heroSprite.move(0, tile_size.y); draw_hero(166, 215, 134, 99); }
    //else 
    //window->draw(heroSprite);
}

void Hero::set_tile_size(sf::Vector2i tile_size) {
    this->tile_size = tile_size;
}

void Hero::draw_hero(int x, int y, int width, int height)
{
    heroSprite.setTextureRect(sf::IntRect(x, y, width, height));
    window->draw(heroSprite);
}
