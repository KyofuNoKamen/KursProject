#pragma once

#include <SFML/Graphics.hpp>

class Fight_interface
{
public:
	Fight_interface(sf::RenderWindow& window, sf::Texture unit_texture);
	void draw_interface();
	void set_unit_texture(sf::Texture unit_texture);
	~Fight_interface();
private:
	sf::RenderWindow* p_window;
	sf::View view;
	sf::Vector2u window_size;
};

