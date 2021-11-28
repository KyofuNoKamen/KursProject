#pragma once
#include "../Headers/Window.h"
#include "../Headers/Hero.h"
#include "../Headers/Entity.h"
#include "../Headers/Enemy.h"
#include "../Headers/Fight_map.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>       
#include "../Headers/Fight_interface.h"
#include "../Headers/Menu.h"
#include "../Headers/Main_menu.h"

#include <winsock2.h>
////////
#include "../Headers/LabLevel.h"
////////


sf::Text fpsText;


Window::Window(int resolution_x, int resolution_y, LabLevel& level, std::string name){
    create_window(resolution_x, resolution_y, name);
    view = new sf::View(sf::FloatRect(0, 0, main_window.getSize().x, main_window.getSize().y));
    //view->setCenter(sf::Vector2f(500, 500));
    main_window.setView(*view);
    setLevel(level);
    level.spawnEnemies();
}

void Window::create_window(int resolution_x, int resolution_y, std::string name)
{
    Window::main_window.create(sf::VideoMode(resolution_x, resolution_y), name, sf::Style::Fullscreen);
	Window::main_window.setFramerateLimit(60);
    Window::main_window.setKeyRepeatEnabled(false);
    main_window.setVerticalSyncEnabled(1);
}

void Window::start() 
{
    int menu_command;
    Menu menu(get_window());

    srand(time(NULL));
    sf::Clock clock_;

    sf::Image heroSpriteset;
    heroSpriteset.loadFromFile("resources/zel.png");
    std::vector<sf::IntRect> spriteRects = {
        sf::IntRect(0, 0, 120, 130), 
        sf::IntRect(0, 780, 120, 130),
        sf::IntRect(0, 910, 120, 130),
        sf::IntRect(0, 520, 120, 130),
        sf::IntRect(0, 650, 120, 130)
    };
    Hero hero(this, this->level, heroSpriteset, spriteRects, 200, 200);


    view->setCenter(hero.sprite.getPosition());

    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);
    
    main_window.setView(*view);

    while (main_window.isOpen())
    {



        sf::Time deltatime = clock_.getElapsedTime();
        clock_.restart();
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view->move(sf::Vector2f(0, -10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                view->move(sf::Vector2f(0, 10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                //view.move(sf::Vector2f(10, 0));
                fight_start(hero.get_texture());
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view->move(sf::Vector2f(-10, 0));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && runEsc == true)
            {
                isEsc = !isEsc;
                runEsc = !runEsc;
            }
            else if (event.type == sf::Event::Resized)
            {
                view = new sf::View(sf::FloatRect(0, 0, main_window.getSize().x, main_window.getSize().y));
                main_window.setView(*view);
            }
          
        }

        
        
        main_window.clear();
        level->Draw(main_window);
        hero.update(deltatime);
        level->EnemiesMakeMicrostep(deltatime);
        drawEnemies();
        renderFPS();

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            runEsc = true;
        if (isEsc == true)
        {   
            menu_command = menu.draw_menu();
            if (menu_command == 1)
            {   
                isEsc = false;
                main_menu();
            }
        }

        main_window.display();
    }

}


void Window::fight_start(sf::Texture hero_texture)
{

    int menu_command;
    Menu menu(get_window());
    /////////////
    //Блок для отправки отряда
     //std::vector<Entity> enemySquad;
     //(*enemySquad).emplace_back(level->GetEnemies(/*[i]*/)); // collection.push_back(object(...));
    std::vector<Entity> enemySquad;
    std::vector<Enemy> enemies = level->GetEnemies();
    for (Enemy& enemy : enemies) { 
        if (-enemy.x <= 100 && -enemy.y <= 100) {
            enemySquad.emplace_back(enemy);
        }
    }
    std::vector<Entity> allySquad;
    std::vector<Enemy> ellies = level->GetEnemies();  //allies = level.GetAllies() - method which will return vector of the ally objects (work in progress) 
    for (Enemy& enemy : enemies) {
        enemySquad.emplace_back(enemy);
    }
     //
     //}
    /////////////
    Fight_map fight("resources/Fight_map.tmx", this, hero_texture, allySquad, enemySquad);
    

    while(1){

        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                view->move(sf::Vector2f(0, -10));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                //view->move(sf::Vector2f(0, 10));
                return;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                //view.move(sf::Vector2f(10, 0));
                fight.draw_map();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                view->move(sf::Vector2f(-10, 0));
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                isEsc = true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && runEsc == true)
            {
                isEsc = !isEsc;
                runEsc = !runEsc;
            }
            main_window.setView(*view);
            
        }

        main_window.clear();
        level->Draw(main_window);
        //hero.update();
        fight.select_tile();
        renderFPS();
       


        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            runEsc = true;
        if (isEsc == true)
        {
            menu_command = menu.draw_menu();
            if (menu_command == 1)
            {
                isEsc = false;
                main_menu();
            }
        }

        main_window.display();
    }
}

void Window::drawEnemies() {
    LabLevel* labLevel = level;
    for (Enemy& enemy : level->GetEnemies())
        main_window.draw(enemy.sprite);
}

void Window::renderFPS() {
    static sf::Clock clock_;
    static float totalElapsed = 0;
    float elapsed = clock_.getElapsedTime().asSeconds();
    totalElapsed += elapsed;
    if (totalElapsed > 0.5f) {
        fpsText.setString(std::to_string(1 / elapsed));
        totalElapsed = 0;
    }
    fpsText.setPosition(main_window.mapPixelToCoords(sf::Vector2i(20, 20)));
    main_window.draw(fpsText);
    clock_.restart();
}

void Window::set_view(sf::View new_view) {
    *view = new_view;
}

sf::RenderWindow& Window::get_window(){
    return main_window;
}

void Window::setLevel(LabLevel& level) {
    this->level = &level;
}

LabLevel& Window::getLevel() {
    return *(this->level);
}

void Window::moveView(int x, int y) {
    view->move(x, y);
    main_window.setView(*view);
}

void Window::setViewCenter(int x, int y) {
    view->setCenter(x, y);
    main_window.setView(*view);
}

sf::Vector2f Window::get_view() {
    return view->getCenter();
}

void Window::main_menu()
{

    int menu_command;
    Main_menu menu(get_window());

    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");
    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);

    view->setCenter(main_window.getSize().x/2, main_window.getSize().y/2);
    main_window.setView(*view);

    while (main_window.isOpen())
    {

        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (event.type == sf::Event::Resized)
            {
                view = new sf::View(sf::FloatRect(0, 0, main_window.getSize().x, main_window.getSize().y));
                main_window.setView(*view);
            }

        }

        main_window.clear();
        renderFPS();


        menu_command = menu.draw_menu();

        if (menu_command == 1) {
            start();
        }

        if (menu_command == 2) {
            //test_net();
        }

        //test_server();

        main_window.display();
    }

    delete& menu;
}

/*
void Window::test_net()
{
    WSADATA WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData);

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int port = 50001;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);

    bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in));

    DWORD nonBlocking = 1;
    ioctlsocket(handle, FIONBIO, &nonBlocking);


    int sent_bytes = sendto(handle, (const char*)"String", 100, 0, (sockaddr*)&address, sizeof(sockaddr_in));


    WSACleanup();
}

void Window::test_server()
{
   
}
*/