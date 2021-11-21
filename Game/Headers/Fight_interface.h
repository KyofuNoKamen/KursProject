#pragma once

#include <SFML/Graphics.hpp>

class Fight_interface
{
public:
	Fight_interface(sf::RenderWindow& window);
	void draw_circle();

private:
	sf::RenderWindow *p_window;
};

