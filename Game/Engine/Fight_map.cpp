#include "../Headers/Fight_map.h"
#include <iostream>

// consider create new class like fightLevel or so
LabLevel g_level;



Fight_map::Fight_map(std::string path_map_fight, Window *main_window, Hero *hero, Enemy enemy/*sf::Texture hero_texture, std::vector<Entity> allySquad, std::vector<Entity> enemySquad*/)
{
	path_map = path_map_fight;
	window = main_window;
	g_level.LoadFromFile(path_map);	

	select_texture.loadFromFile("resources/tile_set_fight.jpg");
	select_sprite.setTexture(select_texture);
	select_sprite.setTextureRect(sf::IntRect(100,100,100,100));
	/*for (Entity& e : enemySquad) {
		std::cout << e.health << std::endl;
		//std::cout << e.chance << std::endl;
	}*/


	
	this->hero_texture = hero_texture;

	///////////
	//// Блок для функции получения отрядов
	//////////
	sf::Texture enemy_texture = enemy.get_texture();
	//fight_interface = new Fight_interface(window->get_window(), this->hero_texture, enemy_texture);
	/*hero->health -= 10;
	std::cout << "Comparison of hero and enemy characteristics" << std::endl;
	std::cout << "Hero health: " << hero->health << std::endl;*/

	//draw_map();
}

void Fight_map::draw_map()
{
	window->setLevel(g_level);
	view = new sf::View(sf::FloatRect(0, 0, window->get_window().getSize().x, window->get_window().getSize().y));
	view->setCenter(sf::Vector2f(1500, 1150));
	window->set_view(*view);
	//window->start();
}

void Fight_map::select_tile()
{
	sf::Vector2i tile_crd;
	tile_crd.x = (sf::Mouse::getPosition().x + (window->get_view().x - window->get_window().getSize().x / 2)) / g_level.GetTileSize().x;
	tile_crd.y = (sf::Mouse::getPosition().y + (window->get_view().y - window->get_window().getSize().y / 2)) / g_level.GetTileSize().y;
	if (tile_crd.x < 6 || tile_crd.y < 7 || tile_crd.y > 14 || tile_crd.x > 23) {		
	}
	else {
		select_sprite.setPosition(tile_crd.x * g_level.GetTileSize().x, tile_crd.y * g_level.GetTileSize().y);
		window->get_window().draw(select_sprite);
	}
	fight_interface->draw_interface();
}
