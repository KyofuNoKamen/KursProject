#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

const sf::IntRect RECT_STAND(0, 0, 120, 130);
const sf::IntRect RECT_DOWN(0, 520, 120, 130);
const sf::IntRect RECT_LEFT(0, 650, 120, 130);
const sf::IntRect RECT_UP(0, 780, 120, 130);
const sf::IntRect RECT_RIGHT(0, 910, 120, 130);

sf::IntRect currentRect = RECT_STAND;

sf::Clock heroClock;

float stepSpeedDivider = 10; // ��� ������, ��� ������� �������� �����
int animationSpeedLimiter = 80; // ��� ������, ��� ������� �������� �������� �����

sf::Vector2f destination; // ���������� ������������� ����� ������������ �����
sf::Vector2f step; // ���, ����� ����������� ������������ �����

Hero::Hero(Window* window) {
    isMoving = false;
    this->window = window;
    // ������� ������� ������������� �� ������� ����� ������ ������� ����
    heroSprite.setOrigin(0, 60);
}

Hero::Hero(Window* window, int x, int y) :Hero(window) {
    heroSprite.move(x, y);
}

void Hero::update() {
    heroSpriteFunction();
    hero_move();
}

void Hero::heroSpriteFunction() {
    sf::Texture hero;
    if (!hero.loadFromFile("resources/zel.png"))
    {
        std::cout << "Error during loading picture from file\n";
    }
    heroSprite.setTexture(hero);
    heroSprite.setTextureRect(currentRect);
    window->get_window().draw(heroSprite);
}

void Hero::hero_move(){
    window->get_window().setKeyRepeatEnabled(false);
    
    // �������� ������������ ����� (���� ���������, ���������� ������ �������������)
    if (isMoving) {
        sf::Vector2f microstep = step / stepSpeedDivider;
        heroSprite.move(microstep);
        if (heroSprite.getPosition() == destination) 
            isMoving = false;
        
        window->moveView(microstep.x, microstep.y);

        // �������� (����� ��������)
        if (heroClock.getElapsedTime().asMilliseconds() > animationSpeedLimiter) {
            currentRect.left = (currentRect.left >= 1080) ? 0 : currentRect.left + 120;
            heroClock.restart();
        }
        // ������������ �� �������, ��� ���������� �� �������� �� ����� �������� ������������
        return;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        step = sf::Vector2f(-tile_size.x, 0);
        currentRect = RECT_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
        step = sf::Vector2f(tile_size.x, 0); 
        currentRect = RECT_RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
        step = sf::Vector2f(0, -tile_size.y); 
        currentRect = RECT_UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        step = sf::Vector2f(0, tile_size.y);
        currentRect = RECT_DOWN;
    }
    else {
        currentRect = RECT_STAND;
        return;
    }

    std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
    destination = heroSprite.getPosition() + step;

    isMoving = true;
    // �������� �� ����������� ������ � ������� �����������
    for (Object obj : collidables) {
        if (obj.rect.contains(destination.x, destination.y)) {
            isMoving = false;
            currentRect = RECT_STAND;
            return;
        }
    }

    // ����� ����� ����, ��������, ����� ������� ��� ������ �������� ������������ �����������

}

void Hero::set_tile_size(sf::Vector2i tile_size) {
    this->tile_size = tile_size;
}

// !!! ����� �� ��� �������?
void Hero::draw_hero(int x, int y, int width, int height)
{
    heroSprite.setTextureRect(sf::IntRect(x, y, width, height));
    window->get_window().draw(heroSprite);
}
