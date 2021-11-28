#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow& window);

	int draw_menu();
	~Menu();

private:
	sf::RenderWindow* p_window;
	sf::View view;
	sf::Vector2u window_size;
};

