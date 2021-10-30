#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

Hero::Hero(Window* window) {
    this->window = window;
    // позиция спрайта отсчитывается от области возле левого нижнего угла
    heroSprite.setOrigin(0, 60);
}

Hero::Hero(Window* window, int x, int y) :Hero(window) {
    heroSprite.move(x, y);
}

void Hero::heroSpriteFunction() {
    sf::Texture hero;
    if (!hero.loadFromFile("resources/spr.png"))
    {
        std::cout << "Error during loading picture from file\n";
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
    window->get_window().setKeyRepeatEnabled(false);
    sf::Vector2f step;
    sf::Vector2f newPos;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        step = sf::Vector2f(-tile_size.x, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { step = sf::Vector2f(tile_size.x, 0);}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { step = sf::Vector2f(0, -tile_size.y);}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { step = sf::Vector2f(0, tile_size.y);}

    std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
    newPos = heroSprite.getPosition() + step;

    bool canMakeStep = true;
    for (Object obj : collidables) {
        if (obj.rect.contains(newPos.x, newPos.y)) {
            canMakeStep = false;
            break;
        }
    }
    if (canMakeStep) {
        heroSprite.move(step);
    }
    //else 
    //window->draw(heroSprite);
}

void Hero::set_tile_size(sf::Vector2i tile_size) {
    this->tile_size = tile_size;
}

void Hero::draw_hero(int x, int y, int width, int height)
{
    heroSprite.setTextureRect(sf::IntRect(x, y, width, height));
    window->get_window().draw(heroSprite);
}
