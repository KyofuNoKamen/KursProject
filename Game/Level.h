#pragma once
#include "Includes.h"

/* Îáúåêò - ýòî âèäèìûé èëè íåâèäèìûé îáúåêò íà êàðòå, ó êîòîðîãî
   ìîæåò áûòü èìÿ, ñïðàéò, è ëþáûå ñâîéñòâà êîòîðûå ìîæíî çàäàòü
*/
struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    float rotation;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

/* Êëàññ âûïîëíÿåò ñëåäóþùèå ôóíêöèè:
    - Çàãðóçêà è îòðèñîâêà êàðòû ñ tmx-ôàéëà
    - Ïîëó÷åíèå îáúåêòîâ íà êàðòå
*/
class Level
{
public:
    bool LoadFromFile(std::string);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
  
    std::vector<Object> GetObjectsWithType(std::string);
/*
    std::vector<Object> GetObjectsWithType(std::string type);
*/
    void Draw(sf::RenderWindow& window);
    sf::Vector2i GetTileSize();

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};

