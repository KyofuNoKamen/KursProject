#pragma once
#include "Includes.h"
#include "Level.h"
#include "Map.h"
#include "Enemy.h"

class Window {
public:
	Window(int, int, std::string);
	Window(int, int, Level&, std::string);
	void start();

	Level& getLevel();
	sf::RenderWindow& get_window();

	void setLevel(Level&);
	void moveView(int, int);
	void mapUpdate(int);

private:
	sf::RenderWindow main_window;
	std::string name;
	int resolution_x,
		resolution_y;
	Level* level;
	sf::View* view;
	
	Enemy* p_easy_enemy;

	void create_window(int, int, std::string);
	void renderFPS();

};