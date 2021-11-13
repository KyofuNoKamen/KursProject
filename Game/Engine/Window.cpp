#include "../Headers/Window.h"
#include "../Headers/Hero.h"
#include "../Headers/Entity.h"
#include "../Headers/Enemy.h"
#include "../Headers/Fight_map.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>       

sf::Vector2f DIRECTIONS[] = {sf::Vector2f(1,0), sf::Vector2f(-1,0), sf::Vector2f(0,1), sf::Vector2f(0,-1)};
sf::Text fpsText;

Window::Window(int resolution_x, int resolution_y, std::string name)
{
    view = new sf::View;

    //view->setCenter(sf::Vector2f(500, 500));
    main_window.setView(*view);
	create_window(resolution_x, resolution_y, name);
}

Window::Window(int resolution_x, int resolution_y, Level& level, std::string name)
    : Window(resolution_x, resolution_y, name)
{
    setLevel(level);
}

void Window::create_window(int resolution_x, int resolution_y, std::string name)
{
    Window::main_window.create(sf::VideoMode(resolution_x, resolution_y), name);
	Window::main_window.setFramerateLimit(60);
    Window::main_window.setKeyRepeatEnabled(false);
}

void Window::start() 
{
    srand(time(NULL));
    sf::Clock clock_;

    Hero hero(this, 200, 200);

    hero.set_tile_size(level->GetTileSize());
    view->setCenter(hero.heroSprite.getPosition());

    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);
    
    main_window.setView(*view);

    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile("resources/ground.jpg");

    for (Object& enemyObj : level->GetObjectsWithType("Enemy")) {
        Enemy* enemy = new Enemy(easyEnemyImage, level, enemyObj.rect.left, enemyObj.rect.top, 100, 100);
        enemies.push_back(*enemy);
    }

    while (main_window.isOpen())
    {
        sf::Time deltatime = clock_.getElapsedTime();
        clock_.restart();
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view->move(sf::Vector2f(0, -10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                view->move(sf::Vector2f(0, 10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                //view.move(sf::Vector2f(10, 0));
                fight_start();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))                
                view->move(sf::Vector2f(-10, 0));
            main_window.setView(*view);
        }
        
        main_window.clear();
        level->Draw(main_window);
        hero.update(deltatime);

        for (Enemy& enemy: enemies) 
            main_window.draw(enemy.sprite);
        
        if (enemyMoving) EnemiesMakeMicrostep(deltatime);

        renderFPS();
        main_window.display();
    }
}

// Every enemy make microstep (if no walls ahead)
// assign enemyMoving = false when all enemies finished movement
void Window::EnemiesMakeMicrostep(sf::Time deltatime) {
    bool isEverybodyFinished = true;
    for (Enemy& enemy : enemies) {
        if (enemy.getIsMoving()) {
            enemy.makeMicrostep(deltatime);
            isEverybodyFinished = false;
        }
    }
    enemyMoving = !isEverybodyFinished;
}

// Every enemy gets the destination point;
// assign enemyMoving = true 
void Window::StartEnemyMoving() {
    for (Enemy& enemy : enemies) {
        sf::Vector2f randomDirection = DIRECTIONS[rand() % 4] * (float)level->GetTileSize().x;
        enemy.makeStepInDirection(randomDirection);
    }
    enemyMoving = true;
}

void Window::fight_start(){

    Fight_map fight("resources/Fight_map.tmx", this);

    while(1){

        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view->move(sf::Vector2f(0, -10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                //view->move(sf::Vector2f(0, 10));
                return;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                //view.move(sf::Vector2f(10, 0));
                fight.draw_map();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view->move(sf::Vector2f(-10, 0));
            main_window.setView(*view);
        }

        main_window.clear();
        level->Draw(main_window);
        //hero.update();
        renderFPS();
        main_window.display();
    }
}

void Window::renderFPS() {
    static sf::Clock clock_;
    static float totalElapsed = 0;
    float elapsed = clock_.getElapsedTime().asSeconds();
    totalElapsed += elapsed;
    if (totalElapsed > 0.5f) {
        fpsText.setString(std::to_string(1 / elapsed));
        totalElapsed = 0;
    }
    fpsText.setPosition(main_window.mapPixelToCoords(sf::Vector2i(20, 20)));
    main_window.draw(fpsText);
    clock_.restart();
}

void Window::mapUpdate(){
    //p_easy_enemy->enemyMove();

}

void Window::set_view(sf::View new_view) {
    *view = new_view;
}

sf::RenderWindow& Window::get_window(){
    return main_window;
}

void Window::setLevel(Level& level) {
    this->level = &level;
}

Level& Window::getLevel() {
    return *(this->level);
}

void Window::moveView(int x, int y) {
    view->move(x, y);
    main_window.setView(*view);
}
