#pragma once

#include "Tiles.h"
#include "tinyxml2.h"


/*
������ ������:
	1. �������� ����� ������ ��������� ����;
	2. ���������� � ���� � �������� �� ����� �����.
*/

/*� ������ ������ ����� �� ������������!*/

class Map
{
public:
	Map(sf::RenderWindow*);
	~Map();
	void draw_map();

	void insert_into_tile_set(std::string arr_key[], sf::IntRect arr_coordinates[], int max);
	sf::IntRect set_texture(std::string tile_name);
private:
	Tiles* grid;
	sf::RenderWindow* main_window;
	std::map <std::string, sf::IntRect> tile_set;
	std::map <std::string, sf::IntRect> ::iterator iterator_tile_set;
	std::vector <std::vector <std::string>> map_vector;
	
	const int size_map = 40;

	void create_map(int size);
};

