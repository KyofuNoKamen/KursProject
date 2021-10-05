#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Map.h"

class Window {
	public:
		Window(int, int, std::string);
		void start();
		
		sf::RenderWindow &get_window();


	private:
		sf::RenderWindow main_window;
		int resolution_x,
			resolution_y;
		std::string name;

		void create_window(int, int, std::string);
};