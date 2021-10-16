#include "Window.h"
#include "Hero.h"

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
}

/*Функция возвращает главное окно*/
sf::RenderWindow &Window::get_window()
{
    return main_window;
}

void Window::setLevel(Level& level) {
    this->level = &level;
}

void Window::start() 
{
    Hero hero(&get_window());

    sf::View view;
    view.setCenter(sf::Vector2f(500, 500));
    main_window.setView(view);

    //Map map(&get_window());

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
        }
        
        main_window.clear();
        //hero.move();
        if (level) level->Draw(main_window);
        hero.heroSpriteFunction();
        main_window.display();
    }
}
