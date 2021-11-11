#include "includes.h"
#include "Hero.h"

const sf::IntRect RECT_STAND(0, 0, 120, 130);
const sf::IntRect RECT_DOWN(0, 520, 120, 130);
const sf::IntRect RECT_LEFT(0, 650, 120, 130);
const sf::IntRect RECT_UP(0, 780, 120, 130);
const sf::IntRect RECT_RIGHT(0, 910, 120, 130);

sf::IntRect currentRect = RECT_STAND;

sf::Clock heroClock;


float stepSpeedDivider = 350; // ��� ������, ��� ������� �������� �����
int animationSpeedLimiter = 60; // ��� ������, ��� ������� �������� �������� �����

/*  old
float stepSpeedDivider = 10; // ÷åì ìåíüøå, òåì áûñòðåå äâèæåíèÿ ãåðîÿ
int animationSpeedLimiter = 80; // ÷åì ìåíüøå, òåì áûñòðåå àíèìàöèÿ äâèæåíèÿ ãåðîÿ
*/

sf::Vector2f destination; // êîîðäèíàòû ÎÊÎÍ×ÀÒÅËÜÍÎÉ ÒÎ×ÊÈ ïåðåäâèæåíèÿ ãåðîÿ
sf::Vector2f step; // øàã, òàêæå íàïðàâëåíèå ïåðåäâèæåíèÿ ãåðîÿ
int status;

Hero::Hero(Window* window) {
    isMoving = false;
    this->window = window;


    if (!texture.loadFromFile("resources/zel.png"))
    {
        std::cout << "Error during loading picture from file\n";
    }
    heroSprite.setTexture(texture);

    // ������� ������� ������������� �� ������� ����� ������ ������� ����

    heroSprite.setOrigin(0, 60);
    if (!texture.loadFromFile("resources/zel.png"))
    {
        std::cout << "Error during loading picture from file\n";
    }
    heroSprite.setTexture(texture);
}

Hero::Hero(Window* window, int x, int y) :Hero(window) {
    heroSprite.move(x, y);
}

void Hero::update(sf::Time deltatime) {
    heroSpriteFunction();

    hero_move(deltatime);
}

void Hero::heroSpriteFunction() {

/* old
hero_move();


Hero::Hero(Window* window) {
    this->window = window;
    speed = 15;
    //collider = sf::Rect<int>(0,100,100,20);
}
Hero::Hero(Window* window, int x, int y):Hero(window) {
    heroSprite.move(x, y);
    colliderSprite.move(x, y + 100);

}

void Hero::heroSpriteFunction() {
    sf::Texture hero;
    if (!hero.loadFromFile("resources/zel.png"))
    {
        std::cout << "Error during loading picture from file\n";
    }
    heroSprite.setTexture(hero);
  */
    heroSprite.setTextureRect(currentRect);
    window->get_window().draw(heroSprite);
}

void Hero::hero_move(sf::Time deltatime){
    window->get_window().setKeyRepeatEnabled(false);
    
    // àíèìàöèÿ ïåðåäâèæåíèÿ ãåðîÿ (ïîêà äåéñòâóåò, óïðàâëåíèå ãåðîåì çàáëîêèðîâàíî)
    if (isMoving) {
        sf::Vector2f microstep = step / stepSpeedDivider * (float)deltatime.asMilliseconds();
        heroSprite.move(microstep);
        window->moveView(microstep.x, microstep.y);

        // àíèìàöèÿ (ñìåíà ñïðàéòîâ)
        if (heroClock.getElapsedTime().asMilliseconds() > animationSpeedLimiter) {
            currentRect.left = (currentRect.left >= 1080) ? 0 : currentRect.left + 120;
            heroClock.restart();
        }

        
        // ���� ����� � ��������� �� ������ ����������, �� ������ ��� ���� � ��������� ��������
        // ���� ��� ����� ����� ����� �� ������ ���� ������� �����
        sf::Vector2f distance = destination - heroSprite.getPosition();
        if (abs(distance.x) <= abs(microstep.x) && abs(distance.y) <= abs(microstep.y)) {
            isMoving = false;
            heroSprite.setPosition(destination);
        }

        // ������������ �� �������, ��� ���������� �� �������� �� ����� �������� ������������

        return;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        step = sf::Vector2f(-tile_size.x, 0);
        currentRect = RECT_LEFT;
        status = 0;
        window->mapUpdate(status);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
        step = sf::Vector2f(tile_size.x, 0); 
        currentRect = RECT_RIGHT;
        status = 1;
        window->mapUpdate(status);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
        step = sf::Vector2f(0, -tile_size.y); 
        currentRect = RECT_UP;
        status = 2;
        window->mapUpdate(status);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        step = sf::Vector2f(0, tile_size.y);
        currentRect = RECT_DOWN;
        status = 3;
        window->mapUpdate(status);
    }
    else {
        currentRect = RECT_STAND;
        status = 4;
        window->mapUpdate(status);
        return;
    }

    std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
    destination = heroSprite.getPosition() + step;

    isMoving = true;
    // Ïðîâåðêà íà âîçìîæíîñòü ïðîéòè â çàäàíîì íàïðàâëåíèè
    for (Object obj : collidables) {
        if (obj.rect.contains(destination.x, destination.y)) {
            isMoving = false;
            currentRect = RECT_STAND;
            return;
        }
    }

    // çäåñü ìîæåò áûòü, íàïðèìåð, âûçîâ ôóíêöèè äëÿ íà÷àëà àíèìàöèè ïåðåäâèæåíèÿ ïðîòèâíèêîâ

}

void Hero::set_tile_size(sf::Vector2i tile_size) {
    this->tile_size = tile_size;
}

// !!! íóæíà ëè ýòà ôóíêöèÿ?
void Hero::draw_hero(int x, int y, int width, int height)
{
    heroSprite.setTextureRect(sf::IntRect(x, y, width, height));
    window->get_window().draw(heroSprite);
/*
    heroSprite.setTextureRect(sf::IntRect(198, 34, 96, 128));

    sf::Texture t;
    t.loadFromFile("resources/test.jpg");
    colliderSprite.setTexture(t);

    float x = 0, y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x -= speed;
        heroSprite.setTextureRect(sf::IntRect(535, 341, -96, 134));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x += speed;
        heroSprite.setTextureRect(sf::IntRect(430, 341, 96, 134)); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        y -= speed;
        heroSprite.setTextureRect(sf::IntRect(35, 161, 107, 162)); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        y += speed;
        heroSprite.setTextureRect(sf::IntRect(166, 215, 134, 99)); 
    }

    // òèï collidable - îáúåêòû ñ êîòîðûìè ãåðîé (êîëëàéäåð) ñòàëêèâàåòñÿ 
    std::vector<Object> collidables = window->getLevel().GetObjectsWithType("collidable");
    
    // íàïðàâëåíèå  êîëëàéäåðà,- òî êóäà ãåðîé ïûòàåòñÿ èäòè
    sf::Rect<int> colliderDirect = sf::Rect<int>(colliderSprite.getGlobalBounds());
    colliderDirect.left += x;
    colliderDirect.top += y;

    bool canMakeStep = true;
    for (Object obj : collidables) {
        if (colliderDirect.intersects(obj.rect)) {
            canMakeStep = false;
            break;
        }
    }
    // ãåðîé ïåðåäâèãàåòñÿ åñëè íåòó ïðåãðàä
    if (canMakeStep) {
        move(x, y);
    }

    window->get_window().draw(heroSprite);
    window->get_window().draw(colliderSprite);
}

void Hero::move(float x, float y) {
    heroSprite.move(x, y);
    colliderSprite.move(x,y);
    window->moveView(x, y);
*/
}
