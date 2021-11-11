#pragma once
#include "Level.h"
#include "Map.h"
#include "Enemy.h"
#include <string>
#include <SFML/Graphics.hpp>


class Window {
	/*public:
		Window(int, int, std::string);
		Window(int, int, Level&, std::string);
		void start();
		Level& getLevel();
		void setLevel(Level&);
		sf::RenderWindow &get_window();
		
	*/
public:
	Window(int, int, std::string);
	Window(int, int, Level&, std::string);
	void start();

	void fight_start();

	Level& getLevel();
	sf::RenderWindow& get_window();

	void setLevel(Level&);
	void moveView(int x, int y);
	void set_view(sf::View new_view);

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

	/*private:
		sf::View view;
		sf::RenderWindow main_window;
		int resolution_x,
			resolution_y;
		std::string name;
		Level* level;
		void create_window(int, int, std::string);
		*/
};