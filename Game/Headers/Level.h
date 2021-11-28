#pragma once
#include <map>
#include <SFML/Graphics.hpp>

const sf::Vector2f DIRECTIONS[] = { sf::Vector2f(0,-1), sf::Vector2f(1,0), sf::Vector2f(0,1), sf::Vector2f(-1,0) };

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

class Level
{
public:
    bool LoadFromFile(std::string);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    std::vector<Object> GetObjectsWithType(std::string);
    std::vector<Object> GetCollidables();
    void Draw(sf::RenderWindow& window);
    sf::Vector2i GetTileSize();

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
    std::vector<Object> collidables;
};

