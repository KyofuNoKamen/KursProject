#include "../Headers/Tiles.h"


/*������� ��� �������� ��������� ����
x_tiles - ���������� ������ � ������
y_tiles - ���������� ������ � ������
border - ������ ������� ������ ��������� ����*/
Tiles::Tiles(sf::RenderWindow *window_ptr, int x_tiles, int y_tiles) 
{
    this->window_ptr = window_ptr;
    this->x_tiles = x_tiles;
    this->y_tiles = y_tiles;
    tile_width = 100;
    tile_height = 100;

    draw_grid();
}

void Tiles::draw_grid()
{
    int points = (x_tiles + y_tiles + 2) * 2; // ���������� ����� ��� �������� �����
    sf::VertexArray line(sf::Lines, points);
    sf::Vector2u resolution = window_ptr->getSize(); // ��������� ���������� ����
    /*���������� ������� ������*/


    /*��������� ���s��������� �����*/
    int j = 0;
    for (int i = 0; i < x_tiles + 1; i++) {
        line[j++].position = sf::Vector2f(tile_width * i, 0);
        line[j++].position = sf::Vector2f(tile_width * i, tile_width * x_tiles);
    }

    /*��������� �������������� �����*/
    for (int i = 0; i < y_tiles + 1; i++) {
        line[j++].position = sf::Vector2f(0, tile_height * i);
        line[j++].position = sf::Vector2f(tile_height * y_tiles, tile_height * i);
    }

    window_ptr->draw(line);
}

sf::Vector2f Tiles::get_tile(sf::Vector2u tile)
{
    sf::Vector2f tile_coordinates;
    tile_coordinates.x = tile.x * tile_width;
    tile_coordinates.y = tile.y * tile_height;
    return tile_coordinates;
}

sf::Vector2f Tiles::get_center(sf::Vector2u tile)
{
    sf::Vector2f tile_coordinates;
    tile_coordinates.x = (tile.x * tile_width) + (tile_width / 2);
    tile_coordinates.y = (tile.y * tile_height) + (tile_height / 2);
    return tile_coordinates;
}

float Tiles::get_tile_width()
{
    return tile_width;
}

float Tiles::get_tile_height()
{
    return tile_height;
}
