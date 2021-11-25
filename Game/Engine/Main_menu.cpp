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
	second_button->set_text("Settings");
	third_button = new Button(100, 350, 700, 100, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	third_button->set_text("Exit");
}
