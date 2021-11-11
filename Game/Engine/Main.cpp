#include "../Headers/Window.h"
#include "../Headers/Level.h"

int main()
{
    // Level - ��� ���� �����
    Level level;
    // �������� �����
    level.LoadFromFile("resources/map.tmx");
    sf::View view;
    view.setCenter(sf::Vector2f(500, 500));

    Window main_window(1000, 1000, level, "Main window");
    main_window.set_view(view);

    main_window.start();

    return 0;
}