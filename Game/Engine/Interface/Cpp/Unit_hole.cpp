#include "../Headers/Unit_hole.h"


Unit_hole::Unit_hole(int x, int y, int width, int height, sf::View view, sf::Texture texture)
{
	old_view = view;
	this->texture = texture;
	unit_hole.setTexture(this->texture);
	unit_hole.setTextureRect(sf::IntRect(0, 0, width, height));

	position = view.getCenter();
	position.x = position.x + x;
	position.y = position.y + y;
	unit_hole.setPosition(position);

}

sf::Sprite Unit_hole::get_unit_hole()
{
	return unit_hole;
}

void Unit_hole::move(sf::View& view)
{
	position.x = unit_hole.getPosition().x - old_view.getCenter().x + view.getCenter().x;
	position.y = unit_hole.getPosition().y - old_view.getCenter().y + view.getCenter().y;
	unit_hole.setPosition(position);
	old_view = view;
}
