#include "Enemy.h" 
#include "Hero.h"
#include "Windows.h"

Enemy::Enemy(sf::Image& image, sf::String Name, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	//obj = window
	if (name == "EasyEnemy") {
		sprite.setTextureRect(sf::IntRect(100, 60, w, h));
		dx = 10;//���� ��������.���� ������ ������ ���������
	}
}
