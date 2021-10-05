#include "Window.h"

Window::Window(int resolution_x, int resolution_y, std::string name) {
	create_window(resolution_x, resolution_y, name);


}

void Window::create_window(int resolution_x, int resolution_y, std::string name) {
    Window::main_window.create(sf::VideoMode(resolution_x, resolution_y), name);
	Window::main_window.setFramerateLimit(60);
}

/*������� ���������� ������� ����*/
sf::RenderWindow &Window::get_window() {
    return main_window;
}

void Window::start() {


    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
        }


        main_window.clear();
        Map map(&get_window());
        main_window.display();
    }
}
