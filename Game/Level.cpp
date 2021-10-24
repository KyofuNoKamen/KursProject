#include "level.h"

#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

// ��������� �������� �������� ���� int
int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}

// ��������� ����� �� .tmx �����
bool Level::LoadFromFile(std::string filename)
{
    XMLDocument levelFile;

    // ��������� XML-�����
    if (levelFile.LoadFile(filename.c_str()))
    {
        std::cout << "Loading level \"" << filename << "\" failed. Error: " << levelFile.ErrorName() << std::endl;
        return false;
    }

    // �������� � ����������� map
    XMLElement* map;
    map = levelFile.FirstChildElement("map");

    // ������ �����: <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="34" tileheight="34">
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // ����� �������� �������� � ������������� ������� �����
    XMLElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - ���� �� �������� � ���������� image
    XMLElement* image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = std::string("resources/") + image->Attribute("source");

    // �������� ��������� �������
    sf::Image img;

    if (!img.loadFromFile(imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    // ������� ����� �� ����� (109, 159, 185)
    // ������-�� � �������� ����� ���� ��� ������ �����, �� � �� ����� �������, ��� 16-������ ������
    // ����� "6d9fb9" ������������� � ����
    img.createMaskFromColor(sf::Color(109, 159, 185));
    // ������ �������� �� �����������
    tilesetImage.loadFromImage(img);
    // �������������� ���������
    tilesetImage.setSmooth(false);

    // �������� ���������� �������� � ����� ��������
    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    // ������ �� ��������������� ����������� (TextureRect)
    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    // ������ �� ������
    XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

        // ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        // ��������� <data>
        XMLElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;
        int lPos = 0,
            rPos = 0;
   
        std::string mapContent(layerDataElement->GetText());
        
        // ������� <data>: id ������ ��������� �������� 
        while ((rPos = mapContent.find(",", rPos+1)) != -1) {
            // id �������� ����� 
            int tileGID = std::stoi(mapContent.substr(lPos, rPos-lPos));
            int subRectToUse = tileGID - firstTileID;
            lPos = rPos + 1;
            // ������������� TextureRect ������� �����
            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            if (++x >= width)
            {
                x = 0;
                if (++y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);
        //����� ���� ������
        layerElement = layerElement->NextSiblingElement("layer");
    }

    // ������ � ���������
    XMLElement* objectGroupElement;

    // ���� ���� ���� ��������
    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // ��������� <object>
            XMLElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                // �������� ��� ������ - ���, ���, �������, etc
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y")) - 100; //�������, ����������� ���������� ��������� � Tiled 

                int width, height;
                float rotation = 0;

                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                }

                if (objectElement->Attribute("rotation"))
                    rotation = atof(objectElement->Attribute("rotation"));

                if(objectElement->Attribute("gid"))
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                

                // ��������� �������
                Object object;
                object.name = objectName;
                object.type = objectType;
                sprite.setRotation(rotation);
                object.sprite = sprite;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // "����������" �������
                XMLElement* properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    XMLElement* prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // ������ ������ � ������
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}


/* ��������� ������ ������ � �������� ������ */
Object Level::GetObject(std::string name){
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

/* ��������� ��� ������� � �������� ������ */
std::vector<Object> Level::GetObjects(std::string name){
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            vec.push_back(objects[i]);

    return vec;
}

std::vector<Object> Level::GetObjectsWithType(std::string type) {
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].type == type)
            vec.push_back(objects[i]);

    return vec;
}

sf::Vector2i Level::GetTileSize()
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow& window)
{
    // ������ ��� ����� 
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
            window.draw(layers[layer].tiles[tile]);

    // ������ ��� �������
    for (Object obj : objects) {
        window.draw(obj.sprite);
        
    }
}
