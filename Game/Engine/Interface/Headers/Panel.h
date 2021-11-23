#pragma once

#include <SFML/Graphics.hpp>

/*
	Task of this class:
		- Create panel for interface in sf::RenderWindow object

	Panel - a box for other interface elements.
*/

class Panel
{
public:
	Panel(int x, int y, int width, int height, sf::View& view); // Coordinates are specified relative to View center
	sf::RectangleShape get_panel();
	void set_border(int border_size);
	void move(sf::View& view);
private:
	sf::RectangleShape panel;
	int border = 0;
	sf::Vector2f position;
	sf::View old_view;
};

