#include "../Headers/Window.h"
#include "../Headers/LabLevel.h"

int main()
{
    // Level - ��� ���� �����
    LabLevel level;
    // �������� �����
    level.LoadFromFile("resources/big_map.tmx");
    //sf::View view;
    //view.setCenter(sf::Vector2f(500, 500));

    Window main_window(1000, 800, level, "Main window");
    //main_window.set_view(view);

    main_window.main_menu();

    return 0;
}