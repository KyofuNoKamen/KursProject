#pragma once
#include "LabLevel.h"
#include "Map.h"
#include "Enemy.h"
#include <string>
#include <SFML/Graphics.hpp>


class Window {
public:
	Window(int, int, LabLevel&, std::string);

	void start();
	void fight_start();

	LabLevel& getLevel();
	sf::RenderWindow& get_window();

    void setLevel(LabLevel&);
	void moveView(int x, int y);
	void setViewCenter(int x, int y);
	void set_view(sf::View new_view);
	void drawEnemies();

private:
	sf::RenderWindow main_window;
	std::string name;
	int resolution_x,
		resolution_y;
	LabLevel* level;
	sf::View* view;

	void create_window(int, int, std::string);
	void renderFPS();
};