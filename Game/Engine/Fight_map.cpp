#include "../Headers/Fight_map.h"
#include <iostream>

// consider create new class like fightLevel or so
LabLevel g_level;
//static int button;



Fight_map::Fight_map(std::string path_map_fight, Window *main_window, std::vector<Entity> allySquad, std::vector<Entity> enemySquad)
{
	path_map = path_map_fight;
	window = main_window;
	g_level.LoadFromFile(path_map);	
	this->allySquad = allySquad;
	this->enemySquad = enemySquad;

	select_texture.loadFromFile("resources/tile_set_fight.jpg");
	select_sprite.setTexture(select_texture);
	select_sprite.setTextureRect(sf::IntRect(100,100,100,100));
	for (Entity& e : allySquad) {
		std::cout << e.health << std::endl;
	}


	
	this->hero_texture = hero_texture;

	///////////
	//// Блок для функции получения отрядов
	//////////
	fight_interface = new Fight_interface(window->get_window(), enemySquad);
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
	
}


void Fight_map::update_frame()
{
	int button = fight_interface->draw_interface();

	if (button == 1)
	{
		new_hero_texture = enemySquad[0].get_texture();
		select_sprite.setTexture(new_hero_texture);
		select_sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

		//sf::Texture test_texture =  enemySquad[0].get_texture();
		/*
		sf::Sprite test_sprite;
		test_sprite.setTexture(test_texture);





		sf::Mouse mouse;
		sf::Vector2f view_position;
		view_position.x = view->getCenter().x - (float)window->get_window().getPosition().x;
		view_position.y = view->getCenter().y - (float)window->get_window().getPosition().y;
		view_position -= sf::Vector2f(window->get_window().getSize().x / 2, window->get_window().getSize().y / 2);
		sf::Vector2f mouse_position(mouse.getPosition().x + view_position.x, mouse.getPosition().y + view_position.y);

		test_sprite.setPosition(mouse_position);
		*/
	}
	select_tile();
}
