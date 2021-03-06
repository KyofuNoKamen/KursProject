#include "../Headers/level.h"
#include "../Headers/tinyxml2.h"
#include <string>
#include <iostream>

using namespace tinyxml2;

// Âîçðàùàåò çíà÷åíèå ñâîéñòâà òèïà int
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

// Çàãðóæàåò êàðòó èç .tmx ôàéëà
bool Level::LoadFromFile(std::string filename)
{
    XMLDocument levelFile;

    // Çàãðóæàåì XML-êàðòó
    if (levelFile.LoadFile(filename.c_str()))
    {
        std::cout << "Loading level \"" << filename << "\" failed. Error: " << levelFile.ErrorName() << std::endl;
        return false;
    }

    // Ðàáîòàåì ñ êîíòåéíåðîì map
    XMLElement* map;
    map = levelFile.FirstChildElement("map");

    // Ïðèìåð êàðòû: <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="34" tileheight="34">
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // Áåðåì îïèñàíèå òàéëñåòà è èäåíòèôèêàòîð ïåðâîãî òàéëà
    XMLElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - ïóòü äî êàðòèíêè â êîíòåéíåðå image
    XMLElement* image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = std::string("resources/") + image->Attribute("source");

    // Ïûòàåìñÿ çàãðóçèòü òàéëñåò
    sf::Image img;

    if (!img.loadFromFile(imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    // Î÷èùàåì êàðòó îò ñâåòà (109, 159, 185)
    // Âîîáùå-òî â òàéëñåòå ìîæåò áûòü ôîí ëþáîãî öâåòà, íî ÿ íå íàøåë ðåøåíèÿ, êàê 16-ðè÷íóþ ñòðîêó
    // âðîäå "6d9fb9" ïðåîáðàçîâàòü â öâåò
    img.createMaskFromColor(sf::Color(109, 159, 185));
    // Ãðóçèì òåêñòóðó èç èçîáðàæåíèÿ
    tilesetImage.loadFromImage(img);
    // Ðàñïëûâ÷àòîñòü çàïðåùåíà
    tilesetImage.setSmooth(false);

    // Ïîëó÷àåì êîëè÷åñòâî ñòîëáöîâ è ñòðîê òàéëñåòà
    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    // Âåêòîð èç ïðÿìîóãîëüíèêîâ èçîáðàæåíèé (TextureRect)
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

    // Ðàáîòà ñî ñëîÿìè
    XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

        // Åñëè ïðèñóòñòâóåò opacity, òî çàäàåì ïðîçðà÷íîñòü ñëîÿ, èíà÷å îí ïîëíîñòüþ íåïðîçðà÷åí
        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        // Êîíòåéíåð <data>
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
        
        // Ïàðñèíã <data>: id òàéëîâ ðàçäåëåíû çàïÿòûìè 
        while ((rPos = mapContent.find(",", rPos+1)) != -1) {
            // id òåêóùåãî òàéëà 
            int tileGID = std::stoi(mapContent.substr(lPos, rPos-lPos));
            int subRectToUse = tileGID - firstTileID;
            lPos = rPos + 1;
            // Óñòàíàâëèâàåì TextureRect êàæäîãî òàéëà
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
        //íîâûé ñëîé òàéëîâ
        layerElement = layerElement->NextSiblingElement("layer");
    }

    // Ðàáîòà ñ îáúåêòàìè
    XMLElement* objectGroupElement;

    // Åñëè åñòü ñëîè îáúåêòîâ
    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // Êîíòåéíåð <object>
            XMLElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                // Ïîëó÷àåì âñå äàííûå - òèï, èìÿ, ïîçèöèÿ, etc
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
                int y = atoi(objectElement->Attribute("y")) - 100; // kostyl`

                int width=0, height=0;
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
                   /* width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;*/
                }


                if (objectElement->Attribute("gid"))
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);

/*
                if (objectElement->Attribute("rotation"))
                    rotation = atof(objectElement->Attribute("rotation"));

                if(objectElement->Attribute("gid"))
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
*/


                // Ýêçåìïëÿð îáúåêòà
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

                // "Ïåðåìåííûå" îáúåêòà
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

                // Ïèõàåì îáúåêò â âåêòîð
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
        collidables = GetObjectsWithType("collidable");

    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

/* Âîçðàùàåò ïåðâûé îáúåêò ñ çàäàííûì èìåíåì */
Object Level::GetObject(std::string name){
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

/* Âîçðàùàåò âñå îáúåêòû ñ çàäàííûì èìåíåì */
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

std::vector<Object> Level::GetCollidables(){
    return collidables;
}

void Level::Draw(sf::RenderWindow& window)
{
    // Ðèñóåì âñå òàéëû 
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
            window.draw(layers[layer].tiles[tile]);

    for (Object obj : objects) 
        window.draw(obj.sprite);
}
