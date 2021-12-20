#include "../Headers/Mod_Heal.h" 
#include <iostream>

Mod_Heal::Mod_Heal(sf::Image image, Level* level, std::vector<sf::IntRect> rects, float X, float Y) :Modificators(level, image, rects, X, Y) {
	sprite.setScale(5, 5);
	modificator_range = 100;
	healing = 5;
	underModificator = false;
}