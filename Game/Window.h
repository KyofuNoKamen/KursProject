#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Level.h"
#include "Map.h"
#include "Enemy.h"

class Window {
	public:
		Window(int, int, std::string);
		Window(int, int, Level&, std::string);
		void start();
		Level& getLevel();
		void setLevel(Level&);
		void mapUpdate(int);
		sf::RenderWindow &get_window();

	private:
		sf::RenderWindow main_window;
		int resolution_x,
			resolution_y;
		std::string name;
		Level* level;
		Enemy* p_easy_enemy;
		void create_window(int, int, std::string);
};