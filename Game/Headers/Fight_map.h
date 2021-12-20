#pragma once
#include <string>
#include "Level.h"
#include "Window.h"
#include "Hero.h"

#include "../Headers/Fight_interface.h"

/*
	������ ������:
		1) �������� ����� ��� ���������� ���
		2) ��������� �����
		3) ��������� � ��������� ���� ������ ��� ���
		4) ������������ ������ �� ���� ���
*/
class Fight_map
{
public:
	/*����������� �������� ���� � �����, ��������� �� ����� ������ � ����� ����������, ��������� �� ������� ����*/
	//Fight_map(std::string path_map_fight/*, *player_squad, *enemy_squad*/, Window *main_window);
	Fight_map(std::string path_map_fight, Window* main_window, Hero *hero, Enemy enemy/*sf::Texture hero_texture, std::vector<Entity> allySquad, std::vector<Entity> enemySquad*/);
	void draw_map();

	void select_tile();

private:
	std::string path_map;
	Window* window;


	sf::View* view;
	
	sf::Texture select_texture;
	sf::Sprite select_sprite;


	Fight_interface* fight_interface;

	sf::Texture hero_texture;
	sf::Sprite hero_sprite;
};

