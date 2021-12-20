#include "../Headers/Enemy.h" 
#include <iostream>
//#include "Window.h"

Enemy::Enemy(sf::Image image, Level* level, std::vector<sf::IntRect> rects, float X, float Y, int squad_counter/*, SquadVector*/) :Entity(level, image, rects, X, Y, squad_counter) {
	// vremenniy kostyl')
	sprite.setScale(5, 5);
	vissibility_distance = 100;
	agility = 60;
	damage = 20;
	//coordinates_x = x;
	//coordinates_y = y;
	std::cout << X << std::endl;  //Выводит
	std::cout << Y << std::endl;
	underModificator = false;

	//squad_counter = 4;
	
	if (squad_counter != 0) {
		//std::vector<Entity> enemy_squad;
		//enemy_squad = squad_vector;
		for (int i = 0; i <= squad_counter; i++) {
			std::cout << i << std::endl;
			//Создание объекта дочернего врага
			/*Enemy* enemy_squad_unit = new Enemy(image, level, rects, X, Y, 0);
			enemy_squad_unit->setAnimationSpeedLimiter(100);
			squad_vector.emplace_back(enemy_squad_unit);*/
		}
	}
}
	
	
