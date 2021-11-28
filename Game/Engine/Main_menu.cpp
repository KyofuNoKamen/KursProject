#include "../Headers/Main_menu.h"
#include "Interface/Headers/Panel.h"
#include "Interface/Headers/Button.h"


static Panel* main_panel;
static Button* first_button;
static Button* second_button;
static Button* third_button;

Main_menu::Main_menu(sf::RenderWindow& window)
{
	p_window = &window;

	view = p_window->getView();

	window_size = p_window->getSize();

	main_panel = new Panel(-(int)(window_size.x / 4), -(int)(window_size.y / 2.2), window_size.x / 4 * 2, (window_size.y / 1.2), view);
	main_panel->set_border(15);

	sf::Texture main_panel_texture;
	main_panel_texture.loadFromFile("resources/menu_panel.png");
	main_panel->set_texture(main_panel_texture);


	first_button = new Button(100, 50, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	first_button->set_text("Start game");
	second_button = new Button(100, 200, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	second_button->set_text("Start UDP sockets test");
	third_button = new Button(100, 350, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	third_button->set_text("Exit");
}

int Main_menu::draw_menu()
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
		return 1;
	}


	second_button->move(main_panel->get_panel().getPosition());
	p_window->draw(second_button->get_button());
	p_window->draw(second_button->get_text());
	if (second_button->clicked(view.getCenter(), window_size, screen_position))
	{
		return 2;
	}


	third_button->move(main_panel->get_panel().getPosition());
	p_window->draw(third_button->get_button());
	p_window->draw(third_button->get_text());
	if (third_button->clicked(view.getCenter(), window_size, screen_position))
	{
		p_window->close();
	}


	return 0;
}



Main_menu::~Main_menu()
{
	delete main_panel;
	delete first_button;
	delete second_button;
	delete third_button;
}
