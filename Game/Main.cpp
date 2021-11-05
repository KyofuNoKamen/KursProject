#include <iostream>
#include "Window.h"
#include "Level.h"


int main()
{
    // Level - это типо карта
    Level level;
    // загрузка карты
    level.LoadFromFile("resources/map.tmx");
    Window main_window(1000, 1000, level, "Main window");
    main_window.start();

    return 0;
}