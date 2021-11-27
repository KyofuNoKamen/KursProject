#pragma once
#include "LabLevel.h"
#include "Map.h"
#include "Enemy.h"
#include <string>
#include <SFML/Graphics.hpp>

#include <SFML/Network.hpp>
#include <SFML/Main.hpp>


class Window {
public:
	Window(int, int, LabLevel&, std::string);

	void start();
	void fight_start(sf::Texture hero_texture);

	LabLevel& getLevel();
	sf::RenderWindow& get_window();

    void setLevel(LabLevel&);
	void moveView(int x, int y);
	void setViewCenter(int x, int y);
	sf::Vector2f get_view();
	void main_menu();
	
	void set_view(sf::View new_view);
	void drawEnemies();


	/*
	void test_net();
	void test_server();
	*/

private:
	sf::RenderWindow main_window;
	std::string name;
	int resolution_x,
		resolution_y;
	LabLevel* level;
	sf::View* view;

	void create_window(int, int, std::string);
	void renderFPS();

	

	bool isEsc = false;
	bool runEsc = true;
};