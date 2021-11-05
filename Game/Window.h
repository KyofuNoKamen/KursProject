#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Level.h"
#include "Map.h"


class Window {
	/*public:
		Window(int, int, std::string);
		Window(int, int, Level&, std::string);
		void start();
		Level& getLevel();
		void setLevel(Level&);
		sf::RenderWindow &get_window();
		void set_view(sf::View new_view);
	*/
public:
	Window(int, int, std::string);
	Window(int, int, Level&, std::string);
	void start();

	Level& getLevel();
	void setLevel(Level&);
	sf::RenderWindow &get_window();
	void moveView(int x, int y);
/*
	void setLevel(Level&);
	Level& getLevel();
	void moveView(int, int);
	sf::View& getView();
	sf::RenderWindow &get_window();
*/

private:
	sf::RenderWindow main_window;
	std::string name;
	int resolution_x,
		resolution_y;
	Level* level;
	sf::View* view;

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