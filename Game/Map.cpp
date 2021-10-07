#include "Map.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>

Map::Map(sf::RenderWindow* window)
{
	this->main_window = window;

	int grid_width = 40;
	int grid_height = 40;

	grid = new Tiles(main_window, grid_width, grid_height);
	std::string map_array[10][10] = 
	{
		{"Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Water", "Water", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Water", "Water", "Nothing", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Ground", "Wall"},
		{"Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall", "Wall"}
	};

	std::map <std::string, sf::IntRect> tile_set;
	std::map <std::string, sf::IntRect> :: iterator iterator_tile_set = tile_set.begin();

	std::string name_tile[4] = { "Ground", "Wall", "Nothing", "Water" };
	sf::IntRect coordinate[4] = { sf::IntRect(0,0,100,100), sf::IntRect(0,100,100,100), sf::IntRect(100,0,100,100), sf::IntRect(100,100,100,100) };
	
	int max = 4;
	insert_into_tile_set(name_tile, coordinate, max);


	draw_map(map_array);
}


//Метод заполняет тайлы спрайтами с нужными текстурами.
void Map::draw_map(std::string map[10][10]) 
{
	sf::Vector2u tile;
	sf::Vector2f coordinates;
	sf::Texture texture;

	sf::IntRect rect(0, 0, 100, 100);

	sf::Sprite sprite;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tile.x = j;
			tile.y = i;
			coordinates = grid->get_tile(tile);
			
			texture.loadFromFile("resources/tile_set.jpg", set_texture(map[i][j]));
			sprite.setTexture(texture);
			sprite.setPosition(coordinates);



			main_window->draw(sprite);	
		}
	}
}


sf::IntRect Map::set_texture(std::string tile_name)
{
	for (iterator_tile_set = tile_set.begin(); iterator_tile_set != tile_set.end(); iterator_tile_set++)
	{
		if (iterator_tile_set->first == tile_name)
		{
			return iterator_tile_set->second;
		}
	}
	return sf::IntRect(0, 0, 100, 100);
}

void Map::insert_into_tile_set(std::string arr_key[], sf::IntRect arr_coordinates[], int max) 
{
	for (int i = 0; i < max; i++)
	{
		tile_set[arr_key[i]] = arr_coordinates[i];
	}
}


Map::~Map()
{
	delete grid;
}
