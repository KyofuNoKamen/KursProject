#pragma once
#include "includes.h"

class Tiles {
public:
	Tiles(sf::RenderWindow *, int, int);
	sf::Vector2f get_tile(sf::Vector2u);
	sf::Vector2f get_center(sf::Vector2u);
	float get_tile_width();
	float get_tile_height();
private:
	int x_tiles,
		y_tiles;
	float tile_width,
		tile_height;
	sf::RenderWindow* window_ptr;

	void draw_grid();
};