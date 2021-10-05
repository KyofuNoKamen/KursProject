#pragma once

#include "Tiles.h"


/*
������ ������:
	1. �������� ����� ������ ��������� ����;
	2. ���������� � ���� � �������� �� ����� �����.
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

