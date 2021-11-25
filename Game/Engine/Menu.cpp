#include "../Headers/Menu.h"
#include "Interface/Headers/Panel.h"
#include "Interface/Headers/Button.h"
#include <iostream>

static Panel* main_panel;
static Button* first_button;
static Button* second_button;
static Button* third_button;

Menu::Menu(sf::RenderWindow& window)
{
	p_window = &window;

	view = p_window->getView();

	window_size = p_window->getSize();

	main_panel = new Panel(-(int)(window_size.x/4), -(int)(window_size.y / 2.2), window_size.x/4*2, (window_size.y / 1.2), view);
	main_panel->set_border(15);
	
	sf::Texture main_panel_texture;
	main_panel_texture.loadFromFile("resources/menu_panel.png");
	main_panel->set_texture(main_panel_texture);

	
	first_button = new Button(100, 50, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	first_button->set_text("Settings");
	second_button = new Button(100, 200, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	second_button->set_text("Return to main menu");
	third_button = new Button(100, 350, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	third_button->set_text("Exit");
}

void Menu::draw_menu()
{
	view = p_window->getView();
	window_size = p_window->getSize();
	sf::Vector2i screen_position = p_window->getPosition();

	main_panel->move(view);
	p_window->draw(main_panel->get_panel());

	first_button->move(main_panel->get_panel().getPosition());
	p_window->draw(first_button->get_button());
	p_window->draw(first_button->get_text());
	if (first_button->clicked(view.getCenter(), window_size, screen_position))
	{
		
	}


	second_button->move(main_panel->get_panel().getPosition());
	p_window->draw(second_button->get_button());
	p_window->draw(second_button->get_text());
	if (second_button->clicked(view.getCenter(), window_size, screen_position))
	{

	}


	third_button->move(main_panel->get_panel().getPosition());
	p_window->draw(third_button->get_button());
	p_window->draw(third_button->get_text());
	if (third_button->clicked(view.getCenter(), window_size, screen_position))
	{
		p_window->close();
	}
}

Menu::~Menu()
{
	delete main_panel;
}
