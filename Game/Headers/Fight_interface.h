#pragma once

#include <SFML/Graphics.hpp>

class Fight_interface
{
public:
	Fight_interface(sf::RenderWindow& window);
	void draw_interface();
	~Fight_interface();
private:
	sf::RenderWindow* p_window;
	sf::View view;
	sf::Vector2u window_size;
};

