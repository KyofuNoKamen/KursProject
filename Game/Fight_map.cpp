#include "Fight_map.h"

Level g_level;

Fight_map::Fight_map(std::string path_map_fight, Window *main_window)
{
	path_map = path_map_fight;
	window = main_window;
	g_level.LoadFromFile(path_map);	
	//draw_map();
}

void Fight_map::draw_map()
{
	window->setLevel(g_level);
	view.setCenter(sf::Vector2f(750, 750));
	window->set_view(view);
	//window->start();
}
