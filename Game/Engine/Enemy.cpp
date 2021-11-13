#include "../Headers/Enemy.h" 
#include "../Headers/Hero.h"
#include <iostream>
//#include "Window.h"

Enemy::Enemy(sf::Image& image, Level* level, float X, float Y, int W, int H) :Entity(level, image, X, Y, W, H) {
	//sprite.setTextureRect(sf::IntRect(100, 60, w, h));
	dx = 10;//даем скорость.этот объект всегда двигается
}
/*
void Enemy::enemyMove() {
        sf::Vector2f step;
        sf::Vector2f newPos;

        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        //    step = sf::Vector2f(-tile_size.x, 0);
        //    currentRect = RECT_LEFT;
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        //    step = sf::Vector2f(tile_size.x, 0);
        //    currentRect = RECT_RIGHT;
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        //    step = sf::Vector2f(0, -tile_size.y);
        //    currentRect = RECT_UP;
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        //    step = sf::Vector2f(0, tile_size.y);
        //    currentRect = RECT_DOWN;
        //}
        //else {
        //    currentRect = RECT_STAND;
        //    return;
        //}

        newPos = sprite.getPosition() + step;

        bool canMakeStep = true;
         for (Object obj : level->GetCollidables()) {
             if (obj.rect.contains(newPos.x, newPos.y)) {
                 canMakeStep = false;
                 std::cout << "There's a wall ahead, I can't get through" <<std::endl;
                 break;
             }
        
         }
    
}
*/
