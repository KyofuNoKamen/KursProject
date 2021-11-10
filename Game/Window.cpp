#include "Window.h"
#include "Hero.h"
#include "Entity.h"
#include "Enemy.h"

sf::Text fpsText;
sf::Clock clock_;

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

/*Ôóíêöèÿ âîçâðàùàåò ãëàâíîå îêíî*/
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

void Window::moveView(int x, int y) {
    view->move(x, y);
    main_window.setView(*view);
}
void Window::start() 
{
    Hero hero(this, 200, 200);
    hero.set_tile_size(level->GetTileSize());
    view->setCenter(hero.heroSprite.getPosition());

    sf::Font font;
    font.loadFromFile("resources/Minecraft.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);

    Object easyEnemyObject = Window::getLevel().GetObject("easyEnemy");
    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile("resources/hellhound.png");
    //Enemy easyEnemy(easyEnemyImage, "EasyEnemy", 200, 200, 100, 100);
    Enemy easyEnemy(easyEnemyImage, "EasyEnemy", level, 200, 200, 100, 100);
    p_easy_enemy = &easyEnemy;

    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view->move(sf::Vector2f(0, -50));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                view->move(sf::Vector2f(0, 50));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                view->move(sf::Vector2f(50, 0));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view->move(sf::Vector2f(-50, 0));

            main_window.setView(*view);

        }
        
        main_window.clear();
        level->Draw(main_window);
        hero.update();
        main_window.draw(easyEnemy.sprite);
        renderFPS();
        main_window.display();
    }
}

void Window::renderFPS() {
    float fps = 1 / clock_.getElapsedTime().asSeconds();
    fpsText.setString(std::to_string(fps));
    fpsText.setPosition(main_window.mapPixelToCoords(sf::Vector2i(20, 20)));
    main_window.draw(fpsText);
    clock_.restart();
}

void Window::mapUpdate(int status )
{
    std::vector<Object> collidables = Window::getLevel().GetObjectsWithType("collidable");
    p_easy_enemy->enemyMove(status, collidables);

}