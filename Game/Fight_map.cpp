#include "Fight_map.h"

Fight_map::Fight_map(std::string path_map_fight, Window* main_window)
{
	path_map = path_map_fight;
	window = main_window;
	draw_map();
}

void Fight_map::draw_map()
{
	Level level;
	level.LoadFromFile(path_map);
	window->setLevel(level);
	sf::View view;
	view.setCenter(sf::Vector2f(750, 750));
	window->set_view(view);
	window->start();
}
