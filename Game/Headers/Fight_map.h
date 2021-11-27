#pragma once
#include <string>
#include "Level.h"
#include "Window.h"
#include "Hero.h"

#include "../Headers/Fight_interface.h"

/*
	Задачи класса:
		1) Открытие карты для проведения боя
		2) Отрисовка карты
		3) Получение и отрисовка всех юнитов для боя
		4) Передвижение юнитов по полю боя
*/
class Fight_map
{
public:
	/*Конструктор получает путь к карте, указатель на отряд игрока и отряд противника, указатель на главное окно*/
	//Fight_map(std::string path_map_fight/*, *player_squad, *enemy_squad*/, Window *main_window);
	Fight_map(std::string path_map_fight, Window* main_window, sf::Texture hero_texture);
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

