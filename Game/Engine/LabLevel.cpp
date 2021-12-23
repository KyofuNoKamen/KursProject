#include "..\Headers\LabLevel.h"

std::vector<Enemy>& LabLevel::GetEnemies(){
	return enemies;
}
std::vector<Mod_Heal>& LabLevel::GetHeals() {
    return heals;
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
    for (Object& enemyObj : GetObjectsWithType("Enemy")) {
        Enemy* enemy = new Enemy(enemyImg, this, enemySpriteRects, enemyObj.rect.left, enemyObj.rect.top, 4);
        enemy->setAnimationSpeedLimiter(100);
        enemies.push_back(*enemy);
    }
}
void LabLevel::spawnHeals() {
   sf::Image healImg;
   healImg.loadFromFile("resources/heal.png");

   std::vector<sf::IntRect> healSpriteRects = {
      sf::IntRect(0, 0, 16, 16),
       sf::IntRect(0, 16, 16, 16),
       sf::IntRect(0, 32, 16, 16),
       sf::IntRect(0, 16, 16, 16),
       sf::IntRect(0, 48, 16, 16)
   };
    for (Object& healObj : GetObjectsWithType("Heal")) {
      Mod_Heal* heal = new Mod_Heal(healImg, this, healSpriteRects, healObj.rect.left, healObj.rect.top);
      //heal->setAnimationSpeedLimiter(100);
      heals.push_back(*heal);
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
