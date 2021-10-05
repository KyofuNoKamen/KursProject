#include "Map.h"
#include <iostream>
#include <string>

Map::Map(sf::RenderWindow* window) {
	this->main_window = window;

	int grid_width = 40;
	int grid_height = 40;

	grid = new Tiles(main_window, grid_width, grid_height);
	std::string map_array[10][10] = {
		{"i", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
	};

	draw_map(map_array);
}


//Метод заполняет тайлы спрайтами с нужными текстурами.
void Map::draw_map(std::string map[10][10]) {
	sf::Vector2u tile;
	sf::Vector2f coordinates;
	sf::Texture texture;
	texture.loadFromFile("resources/texture.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tile.x = i;
			tile.y = j;
			coordinates = grid->get_tile(tile);
			sprite.setPosition(coordinates);

			main_window->draw(sprite);	
		}
	}
}

Map::~Map()
{
	delete grid;
}
