#include "../Headers/Panel.h"
#include <iostream>

Panel::Panel(int x, int y, int width, int height, sf::View& view)
{
	old_view = view;
	panel = sf::RectangleShape(sf::Vector2f(width - border, height - border));
	position = view.getCenter();
	position.x = position.x + x + border;
	position.y = position.y + y + border;
	panel.setPosition(position);
	
	panel_texture.loadFromFile("resources/panel.jpg");
	panel.setTexture(&panel_texture);
}

sf::RectangleShape Panel::get_panel()
{
	return panel;
}

void Panel::set_border(int border_size)
{
	border = border_size;
	panel.setSize(sf::Vector2f(panel.getSize().x - (border * 2), panel.getSize().y - (border * 2)));
	panel.setPosition(sf::Vector2f(panel.getPosition().x + border, panel.getPosition().y + border));
}

void Panel::move(sf::View& view)
{
	position.x = panel.getPosition().x - old_view.getCenter().x + view.getCenter().x;
	position.y = panel.getPosition().y - old_view.getCenter().y + view.getCenter().y;
	panel.setPosition(position);
	old_view = view;
}

void Panel::set_texture(sf::Texture texture)
{
	panel_texture = texture;
	panel.setTexture(&panel_texture, true);
}

