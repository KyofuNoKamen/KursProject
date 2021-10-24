#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

/* Объект - это видимый или невидимый объект на карте, у которого
   может быть имя, спрайт, и любые свойства которые можно задать
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

/* Класс выполняет следующие функции:
    - Загрузка и отрисовка карты с tmx-файла
    - Получение объектов на карте
*/
class Level
{
public:
    bool LoadFromFile(std::string);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    std::vector<Object> GetObjectsWithType(std::string type);
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

