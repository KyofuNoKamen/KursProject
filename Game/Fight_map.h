#pragma once
#include <string>
#include "Level.h"
#include "Window.h"

/*
	������ ������:
		1) �������� ����� ��� ���������� ���
		2) ��������� �����
		3) ��������� � ��������� ���� ������ ��� ���
		4) ������������ ������ �� ���� ���
*/
class Fight_map
{
public:
	/*����������� �������� ���� � �����, ��������� �� ����� ������ � ����� ����������, ��������� �� ������� ����*/
	Fight_map(std::string path_map_fight/*, *player_squad, *enemy_squad*/, Window *main_window);

private:
	std::string path_map;
	Window* window;
	
	void draw_map();
};

