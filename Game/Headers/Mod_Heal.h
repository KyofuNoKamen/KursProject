#pragma once
#include "Modificators.h"
#include <vector>

class Mod_Heal :public Modificators {
public:
	Mod_Heal(sf::Image, Level*, std::vector<sf::IntRect>, float, float);
	int healing;
};