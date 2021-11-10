#include "Window.h"
#include "Hero.h"

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
	Window::main_window.setFramerateLimit(120);
    Window::main_window.setKeyRepeatEnabled(false);
}

/*Функция возвращает главное окно*/
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
    sf::Clock clock;

    Hero hero(this, 200, 200);
    hero.set_tile_size(level->GetTileSize());
    view->setCenter(hero.heroSprite.getPosition());

    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);

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
        hero.update(clock.getElapsedTime());
        renderFPS();
        clock.restart();
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
