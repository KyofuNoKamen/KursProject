#include "Window.h"
#include "Hero.h"
#include "Fight_map.h"

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
    Window::main_window.create(sf::VideoMode(resolution_x, resolution_y), name, sf::Style::Fullscreen);
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

    //sf::View view;
    //view.setCenter(sf::Vector2f(500, 500));
    
    main_window.setView(view);

    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view.move(sf::Vector2f(0, -10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                view.move(sf::Vector2f(0, 10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    //view.move(sf::Vector2f(10, 0));
                Fight_map fight("resources/Fight_map.tmx", this);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view.move(sf::Vector2f(-10, 0));
            main_window.setView(view);
            hero.hero_move();
        }
        
        main_window.clear();
        if (level) level->Draw(main_window);
        hero.heroSpriteFunction();
        //if (timer%5 == 0)
        
        //hero.draw_hero();

        main_window.display();
        timer++;
    }
}

void Window::set_view(sf::View new_view) {
    view = new_view;
}
