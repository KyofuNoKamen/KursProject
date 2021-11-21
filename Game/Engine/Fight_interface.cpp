#include "../Headers/Fight_interface.h"

Fight_interface::Fight_interface(sf::RenderWindow& window)
{
	p_window = &window;
}

void Fight_interface::draw_circle()
{
	sf::CircleShape circle(10, 30);
	p_window->draw(circle);
}
