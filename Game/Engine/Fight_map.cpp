#include "../Headers/Fight_map.h"

// consider create new class like fightLevel or so
LabLevel g_level;

Fight_map::Fight_map(std::string path_map_fight, Window *main_window)
{
	path_map = path_map_fight;
	window = main_window;
	g_level.LoadFromFile(path_map);	
	draw_map();
}

void Fight_map::draw_map()
{
	window->setLevel(g_level);
	view = new sf::View(sf::FloatRect(0, 0, window->get_window().getSize().x, window->get_window().getSize().y));
	view->setCenter(sf::Vector2f(1500, 1150));
	window->set_view(*view);
	//window->start();
}
