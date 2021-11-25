#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(int x, int y, int width, int height, sf::Vector2f panel_position, sf::Vector2f window_position, sf::Vector2u window_size);
	sf::RectangleShape get_button();
	void set_border(int border_size);
	bool clicked(sf::Vector2f window_position, sf::Vector2u window_size, sf::Vector2i screen_position);
	void move(sf::Vector2f view);
	void set_text(std::string string);
	sf::Text get_text();
private:
	sf::RectangleShape button;
	int border = 0;

	sf::Vector2f old_view;
	sf::Vector2f start_position;
	sf::Vector2f view_position;
	sf::Vector2f position;
	bool is_pressed = false;

	sf::Text text;
	sf::Font font;
	sf::Texture button_texture;
};

