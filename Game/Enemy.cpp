#include "Enemy.h" 
#include "Hero.h"
#include "Tiles.h"
#include "Windows.h"

void Enemy::update(int status)
{
	if (name == "EasyEnemy") {
        sf::Vector2f step;
        sf::Vector2f newPos;

       newPos = sprite.getPosition() + step;

        bool canMakeStep = true;
        /*for (Object obj : collidables) {
            if (obj.rect.contains(newPos.x, newPos.y)) {
                canMakeStep = false;
                break;
            }*/

        if (canMakeStep) {
            if (status == 0) {
                std::cout << "st 0 - Left" << std::endl;
                step = sf::Vector2f(-100, 0);
                sprite.move(step);
            }
            if (status == 1) {
                std::cout << "st 1 - Right" << std::endl;
                step = sf::Vector2f(100, 0);
                sprite.move(step);
            }
            if (status == 2) {
                std::cout << "st 2 - Up" << std::endl;
                step = sf::Vector2f(0, -100);
                sprite.move(step);
            }
            if (status == 3) {
                std::cout << "st 3 - Down" << std::endl;
                step = sf::Vector2f(0, 100);
                sprite.move(step);
            }
        }
	}
}
