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
private:
	Tiles* grid;
	sf::RenderWindow* main_window;
	
	void draw_map(std::string map[10][10]);

};

