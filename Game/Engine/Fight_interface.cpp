#include "../Headers/Fight_interface.h"
#include "Interface/Headers/Panel.h"
#include "Interface/Headers/Button.h"
#include "Interface/Headers/Unit_hole.h"
#include <iostream>


static Panel *main_panel;

static Unit_hole *unit_panel;

static Button *first_button;
static Button *second_button;

static sf::View unit_panel_view; //f_tst


Fight_interface::Fight_interface(sf::RenderWindow& window, sf::Texture hero_texture, sf::Texture enemy_texture/*, std::vector<Entity> enemySquad*/)
{
	p_window = &window;

	view = p_window->getView();

	window_size = p_window->getSize();


	/*main_panel = new Panel(-(int)(window_size.x / 2), (window_size.y / 3), window_size.x, (window_size.y / 6), view);
	main_panel->set_border(15);
	

	first_button = new Button(70, 10, 200, main_panel->get_panel().getSize().y - 20, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	second_button = new Button(300, 10, 200, main_panel->get_panel().getSize().y - 20, main_panel->get_panel().getPosition(), view.getCenter(), window_size);


	
	
	unit_panel = new Unit_hole(first_button->get_button().getSize().x / 2 - 50, first_button->get_button().getSize().y / 2 - 50, 100, 100, unit_panel_view, hero_texture);
	unit_panel = new Unit_hole(second_button->get_button().getSize().x / 2 - 50, second_button->get_button().getSize().y / 2 - 50, 100, 100, unit_panel_view, enemy_texture);*/
}

void Fight_interface::draw_interface()
{
	view = p_window->getView();
	

	unit_panel_view.setCenter(first_button->get_button().getPosition()); //F_tst
	
	
	window_size = p_window->getSize();
	sf::Vector2i screen_position = p_window->getPosition();


	main_panel->move(view);
	p_window->draw(main_panel->get_panel());

	first_button->move(main_panel->get_panel().getPosition());
	p_window->draw(first_button->get_button());
	first_button->clicked(view.getCenter(), window_size, screen_position);

	second_button->move(main_panel->get_panel().getPosition());
	p_window->draw(second_button->get_button());
	second_button->clicked(view.getCenter(), window_size, screen_position);


	unit_panel->move(unit_panel_view);
	p_window->draw(unit_panel->get_unit_hole());
}

Fight_interface::~Fight_interface()
{
	delete main_panel;
	delete first_button;
	delete second_button;
}

void Fight_interface::set_unit_texture(sf::Texture unit_texture)
{
}