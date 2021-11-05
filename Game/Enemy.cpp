#include "Enemy.h" 
#include "Hero.h"

Enemy::Enemy(sf::Image& image, sf::String Name, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	if (name == "EasyEnemy") {
		sprite.setTextureRect(sf::IntRect(100, 60, w, h));
		dx = 10;//даем скорость.этот объект всегда двигается
	}
}
void Enemy::enemyMove(int status, std::vector<Object> collidables) {
    if (name == "EasyEnemy") {
        sf::Vector2f step;
        sf::Vector2f newPos;

        //std::vector<Object> collidables = Window::getLevel().GetObjectsWithType("collidable");
        newPos = sprite.getPosition() + step;

        bool canMakeStep = true;
         for (Object obj : collidables) {
             if (obj.rect.contains(newPos.x, newPos.y)) {
                 canMakeStep = false;
                 std::cout << "There's a wall ahead, I can't get through" <<std::endl;
                 break;
             }

        if (canMakeStep) {
            if (status == 0) {
                std::cout << "st 0 - Left" << std::endl;
                step = sf::Vector2f(-100, 0);
                sprite.move(step);
            }
            else if (status == 1) {
                std::cout << "st 1 - Right" << std::endl;
                step = sf::Vector2f(100, 0);
                sprite.move(step);
            }
            else if (status == 2) {
                std::cout << "st 2 - Up" << std::endl;
                step = sf::Vector2f(0, -100);
                sprite.move(step);
            }
            else if (status == 3) {
                std::cout << "st 3 - Down" << std::endl;
                step = sf::Vector2f(0, 100);
                sprite.move(step);
            }
            /*else {
                std::cout << "st 4 - What?" << std::endl;
                step = sf::Vector2f(0, 1);
                p_easy_enemy->sprite.move(step);
            }*/
        }
        }
    }
}