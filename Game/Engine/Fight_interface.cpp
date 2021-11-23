#include "../Headers/Fight_interface.h"
#include "Interface/Headers/Panel.h"
#include "Interface/Headers/Button.h"


static Panel *main_panel;
static Button *first_button;
static Button *second_button;


Fight_interface::Fight_interface(sf::RenderWindow& window)
{
	p_window = &window;

	view = p_window->getView();

	window_size = p_window->getSize();

	main_panel = new Panel(-(int)(window_size.x / 2), (window_size.y / 3), window_size.x, (window_size.y / 6), view);
	main_panel->set_border(15);

	first_button = new Button(10, 10, 200, main_panel->get_panel().getSize().y - 20, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
	second_button = new Button(230, 10, 200, main_panel->get_panel().getSize().y - 20, main_panel->get_panel().getPosition(), view.getCenter(), window_size);
}

void Fight_interface::draw_interface()
{
	view = p_window->getView();
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
}

Fight_interface::~Fight_interface()
{
	delete main_panel;
	delete first_button;
	delete second_button;
}