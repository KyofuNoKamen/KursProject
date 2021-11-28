#pragma once
#include "Level.h"
#include "Enemy.h"
class LabLevel : public Level{
public:
	std::vector<Enemy>& GetEnemies();
	void spawnEnemies();
	void EnemiesMakeMicrostep(sf::Time);
	void StartEnemyMoving();
private:
	bool enemyMoving = false;
	std::vector<Enemy> enemies;
};

