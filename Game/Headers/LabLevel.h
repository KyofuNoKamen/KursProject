#pragma once
#include "Level.h"
#include "Enemy.h"
#include "Mod_Heal.h"
class LabLevel : public Level{
public:
	std::vector<Enemy>& GetEnemies();
	std::vector<Mod_Heal>& GetHeals();
	void spawnEnemies();
	void EnemiesMakeMicrostep(sf::Time);
	void StartEnemyMoving();
private:
	bool enemyMoving = false;
	std::vector<Enemy> enemies;
	std::vector<Mod_Heal> heals;
};

