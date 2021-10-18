#include "Map.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <vector>

Map::Map(sf::RenderWindow* window)
{
	this->main_window = window;

	std::vector <std::vector <std::string>>;

	create_map(size_map);



	int grid_width = 5;
	int grid_height = 5;



	grid = new Tiles(main_window, grid_width, grid_height);
}


//Метод заполняет тайлы спрайтами с нужными текстурами.
void Map::draw_map() 
{
	/*
	std::map <std::string, sf::IntRect> tile_set;
	std::map <std::string, sf::IntRect> ::iterator iterator_tile_set = tile_set.begin();

	std::string name_tile[4] = { "Ground", "Wall", "Nothing", "Water" };
	sf::IntRect coordinate[4] = { sf::IntRect(0,0,100,100), sf::IntRect(0,100,100,100), sf::IntRect(100,0,100,100), sf::IntRect(100,100,100,100) };

	int max = 4;
	insert_into_tile_set(name_tile, coordinate, max);

	//sf::Vector2u tile;
	sf::Vector2f coordinates;
	sf::Texture texture;

	texture.loadFromFile("resources/tile_set.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	for (int i = 0; i < size_map; i++)
	{
		for (int j = 0; j < size_map; j++)
		{
			coordinates = grid->get_tile(sf::Vector2u(i, j));
			
			sprite.setTextureRect(set_texture(map_vector[i][j]));
			sprite.setPosition(coordinates);

			main_window->draw(sprite);
		}
	}
	*/

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

void Map::create_map(int size)
{
	std::vector <std::string> string_map;
	for (int j = 0; j < size/2; j++)
	{
		string_map.push_back("Ground");
		std::cout << string_map[j] << " ";
		
		
		string_map.push_back("Water");
		std::cout << string_map[j] << " ";
	}

	std::cout << std::endl;
	for (int i = 0; i < size; i++)
	{
		map_vector.push_back(string_map);
	}

}
