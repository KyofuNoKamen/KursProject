#pragma once
#include <string>

class Fight
{
public:
	Fight(); // При запуске боя в конструктор должен передаваться отряд игрока, отряд противника и карта.

private:
	int player_squad;
	int enemy_squad;
	std::string map_path;
};
