#include <iostream>
#include "Window.h"
#include "Level.h"


int main()
{
    // Level - это типо карта
    Level level;
    // загрузка карты
    level.LoadFromFile("resources/map.tmx");
    sf::View view;
    view.setCenter(sf::Vector2f(500, 500));

    Window main_window(1000, 1000, level, "Main window");
    main_window.set_view(view);

    main_window.start();

    return 0;
}