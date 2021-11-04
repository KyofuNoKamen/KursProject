#include "Window.h"
#include "Hero.h"
#include "Entity.h"
#include "Enemy.h"
#include <list>

Window::Window(int resolution_x, int resolution_y, std::string name)
{
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

/*������� ���������� ������� ����*/
sf::RenderWindow &Window::get_window()
{
    return main_window;
}

void Window::setLevel(Level& level) {
    this->level = &level;
}

Level& Window::getLevel() {
    return *(this->level);
}

void Window::start() 
{
    int timer = 0; //������, ������� ������� ���������� ������. ������ 60 ������ = 1 �������

    Hero hero(this, 200, 200);
    hero.set_tile_size(level->GetTileSize());

    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile("resources/hellhound.png");

    Enemy easyEnemy(easyEnemyImage,"EasyEnemy", 0, 0, 100, 100);
    p_easy_enemy = &easyEnemy;

    sf::View view;
    view.setCenter(sf::Vector2f(500, 500));
    main_window.setView(view);


    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view.move(sf::Vector2f(0, -50));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                view.move(sf::Vector2f(0, 50));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    view.move(sf::Vector2f(50, 0));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view.move(sf::Vector2f(-50, 0));
            main_window.setView(view);
            hero.hero_move();
        }
        
        main_window.clear();
        if (level) level->Draw(main_window);
        hero.heroSpriteFunction();
        //if (timer%5 == 0) 
        main_window.draw(easyEnemy.sprite);
        main_window.display();
        timer++;
    }
}
void Window::mapUpdate(int status)
{
    if (p_easy_enemy->name == "EasyEnemy") {
        sf::Vector2f step;
        sf::Vector2f newPos;

        std::vector<Object> collidables = Window::getLevel().GetObjectsWithType("collidable");
        newPos = p_easy_enemy->sprite.getPosition() + step;

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
                    p_easy_enemy->sprite.move(step);
                }
                if (status == 1) {
                    std::cout << "st 1 - Right" << std::endl;
                    step = sf::Vector2f(100, 0);
                    p_easy_enemy->sprite.move(step);
                }
                if (status == 2) {
                    std::cout << "st 2 - Up" << std::endl;
                    step = sf::Vector2f(0, -100);
                    p_easy_enemy->sprite.move(step);
                }
                if (status == 3) {
                    std::cout << "st 3 - Down" << std::endl;
                    step = sf::Vector2f(0, 100);
                    p_easy_enemy->sprite.move(step);
                }
            }
        }
    }
}