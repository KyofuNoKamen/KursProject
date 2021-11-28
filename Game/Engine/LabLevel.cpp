#include "..\Headers\LabLevel.h"

std::vector<Enemy>& LabLevel::GetEnemies(){
	return enemies;
}

void LabLevel::spawnEnemies() {
    sf::Image enemyImg;
    enemyImg.loadFromFile("resources/mushroom.png");

    std::vector<sf::IntRect> enemySpriteRects = {
       sf::IntRect(0, 0, 16, 16),
        sf::IntRect(0, 16, 16, 16),
        sf::IntRect(0, 32, 16, 16),
        sf::IntRect(0, 16, 16, 16),
        sf::IntRect(0, 48, 16, 16)
    };

    //std::vector<sf::IntRect> enemySpriteRects = {
    //   sf::IntRect(0, 0, 16, 32),
    //   sf::IntRect(0, 32, 16, 32),
    //   sf::IntRect(0, 64, 16, 32),
    //   sf::IntRect(0, 0, 16, 32),
    //   sf::IntRect(0, 96, 16, 32)
    //};

    for (Object& enemyObj : GetObjectsWithType("Enemy")) {
        Enemy* enemy = new Enemy(enemyImg, this, enemySpriteRects, enemyObj.rect.left, enemyObj.rect.top, 69);
        enemy->setAnimationSpeedLimiter(100);
        enemies.push_back(*enemy);
    }
}

// Every enemy make microstep (if no walls ahead)
// assign enemyMoving = false when all enemies finished movement
void LabLevel::EnemiesMakeMicrostep(sf::Time deltatime) {
    if (enemyMoving) {
         bool isEverybodyFinished = true;
         for (Enemy& enemy : enemies) {
             if (enemy.getIsMoving()) {
                 enemy.makeMicrostep(deltatime);
                 isEverybodyFinished = false;
             }
         }
         enemyMoving = !isEverybodyFinished;
    }
}

// Every enemy gets the destination point;
// assign enemyMoving = true 
void LabLevel::StartEnemyMoving() {
    for (Enemy& enemy : enemies) {
        sf::Vector2f randomDirection = DIRECTIONS[rand() % 4];
        enemy.makeStepInDirection(randomDirection);
    }
    enemyMoving = true;
}
