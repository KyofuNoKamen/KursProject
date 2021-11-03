#include <iostream>
#include "Window.h"
#include "Level.h"


/*int main()
{
    // Level - ��� ���� �����
    Level level;
    level.LoadFromFile("resources/map.tmx");
    Window main_window(1000, 1000, level, "Main window");

    main_window.start();

    return 0;
}*/

int main()
{
    // Level - ��� ���� �����
    Level level;
    level.LoadFromFile("resources/Fight_map.tmx");
    Window main_window(1920, 1080, level, "Main window");
    sf::View view;
    view.setCenter(sf::Vector2f(960, 540));
    main_window.start();



    return 0;
}