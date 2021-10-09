#pragma once

#include "Tiles.h"


/*
Задачи класса:
	1. Создание карты поверх тайлового поля;
	2. Сохранение в файл и загрузка из файла карты.
*/

class Map
{
public:
	Map(sf::RenderWindow*);
	~Map();
	void insert_into_tile_set(std::string arr_key[], sf::IntRect arr_coordinates[], int max);
	sf::IntRect set_texture(std::string tile_name);
private:
	Tiles* grid;
	sf::RenderWindow* main_window;
	std::map <std::string, sf::IntRect> tile_set;
	std::map <std::string, sf::IntRect> ::iterator iterator_tile_set;
	
	void draw_map(std::vector<std::vector<std::string>> &map);
};

