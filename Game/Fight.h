#pragma once
#include <string>

class Fight
{
public:
	Fight(); // ��� ������� ��� � ����������� ������ ������������ ����� ������, ����� ���������� � �����.

private:
	int player_squad;
	int enemy_squad;
	std::string map_path;
};
