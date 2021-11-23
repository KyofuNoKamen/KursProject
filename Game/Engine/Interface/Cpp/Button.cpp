#include "../Headers/Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, sf::Vector2f panel_position, sf::Vector2f window_position, sf::Vector2u window_size)
{
	button = sf::RectangleShape(sf::Vector2f(width - border, height - border));

	view_position = window_position;
	view_position -= sf::Vector2f(window_size.x/2, window_size.y/2);


	start_position = panel_position;

	old_view = start_position;

	position = start_position;
	position.x = position.x + x + border;
	position.y = position.y + y + border;
	button.setPosition(position);
	button.setFillColor(sf::Color::Blue);
}

sf::RectangleShape Button::get_button()
{
	return button;
}

void Button::set_border(int border_size)
{
	border = border_size;
	button.setSize(sf::Vector2f(button.getSize().x - (border * 2), button.getSize().y - (border * 2)));
	button.setPosition(sf::Vector2f(button.getPosition().x + border, button.getPosition().y + border));
}

bool Button::clicked(sf::Vector2f window_position, sf::Vector2u window_size, sf::Vector2i screen_position)
{
	sf::Mouse mouse;
	view_position.x = window_position.x - (float)screen_position.x;
	view_position.y = window_position.y - (float)screen_position.y;
	view_position -= sf::Vector2f(window_size.x / 2, window_size.y / 2);
	sf::Vector2f mouse_position(mouse.getPosition().x + view_position.x, mouse.getPosition().y + view_position.y);
	if (mouse_position.x > button.getPosition().x && mouse_position.y > button.getPosition().y && mouse_position.x < button.getPosition().x + button.getSize().x && mouse_position.y < button.getPosition().y + button.getSize().y)
	{
		if (is_pressed)
		{
			if (!mouse.isButtonPressed(mouse.Left))
			{
				std::cout << "released" << std::endl;
				is_pressed = false;
				return true;
			}
		}		
	else if (mouse.isButtonPressed(mouse.Left))
		{
			//std::cout << "pressed" << std::endl;

			is_pressed = true;	
		}	
		return false;
	}
}

void Button::move(sf::Vector2f view)
{
	position.x = button.getPosition().x - old_view.x + view.x;
	position.y = button.getPosition().y - old_view.y + view.y;
	button.setPosition(position);
	old_view = view;
}