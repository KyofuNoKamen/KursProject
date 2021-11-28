#pragma once
#include <SFML/Graphics.hpp>


class Unit_hole
{
public:
	Unit_hole(int x, int y, int width, int height, sf::View view, sf::Texture texture);

	sf::Sprite get_unit_hole();

	void move(sf::View& view);


private:
	sf::View old_view;
	sf::Sprite unit_hole;
	sf::Vector2f position;
	sf::Texture texture;
};

