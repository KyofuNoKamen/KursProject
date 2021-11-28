#pragma once

#include <SFML/Graphics.hpp>

class Main_menu
{
public:
	Main_menu(sf::RenderWindow& window);

	int draw_menu();
	~Main_menu();

private:
	sf::RenderWindow* p_window;
	sf::View view;
	sf::Vector2u window_size;
};

