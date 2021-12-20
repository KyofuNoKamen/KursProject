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
#include "../Headers/Networking.h"
#include "../Headers/NetworkClient.h"
#include <winsock2.h>

sf::Text fpsText;
vector<Hero> playersVec;
string clientName;

sf::IpAddress S_Ip = sf::IpAddress::IpAddress::LocalHost;
int S_port = 53948;

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
    NetworkClient netC;
    netC.init();
    

    sf::Packet data_packet;


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

    sf::Texture t_player;
    t_player.loadFromFile("resources/zel.png");
    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");

    Hero hero(this, this->level, heroSpriteset, spriteRects, 200, 200, "player");
    
    getUserInputData(hero.name);

    vector<string> namesVec;
    netC.registerOnServer(S_Ip, S_port, hero.name);

    //getUserInputData(player.name);

    netC.receiveConnectedClientsNames(namesVec);
    for (int i = 0; i < namesVec.size(); i++)
    {
        addPlayer(t_player, font, namesVec[i]);
    }

    sf::Packet receivedDataPacket;
    sf::Packet sendDataPacket;

    view->setCenter(hero.sprite.getPosition());

    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);
    
    main_window.setView(*view);

    while (main_window.isOpen()){
        bool isWindowVisible = true;
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


 

        if (netC.receiveData(receivedDataPacket, S_Ip, S_port) == sf::Socket::Status::Done)
        {
            if (receivedDataPacket.getDataSize() > 0)
            {
                string s;
                if (receivedDataPacket >> s)
                {
                    if (s == "NEW")
                    {
                        if (receivedDataPacket >> s)
                        {
                            if (s != clientName)
                            {
                                addPlayer(t_player, font, s);
                                cout << "New player connected: " << playersVec.back().name << endl;
                            }
                        }
                    }
                    if (s == "DATA")
                    {
                        while (!receivedDataPacket.endOfPacket())
                        {
                            float x, y;
                            receivedDataPacket >> s;
                            std::cout << s << " - ";
                            receivedDataPacket >> x;
                            std::cout << x << " - ";
                            receivedDataPacket >> y;
                            std::cout << y << std::endl;
                            for (int i = 0; i < playersVec.size(); i++)
                            {
                                if (s == playersVec[i].name)
                                {
                                    playersVec[i].sprite.setPosition(sf::Vector2f(x, y));
                                    playersVec[i].x = x;
                                    playersVec[i].y = y;
                                    std::cout << playersVec[i].name << ": " << playersVec[i].x << " " << playersVec[i].y << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        sendDataPacket.clear();
        sendDataPacket << "DATA" << hero.x << hero.y;
        netC.sendData(sendDataPacket);

        for (int i = 0; i < playersVec.size(); i++)
        {
            playersVec[i].update(deltatime);
        }

        if (main_window.hasFocus())
        {
            hero.update(deltatime);
            setViewCenter(hero.sprite.getPosition().x, hero.sprite.getPosition().y);
        }

        main_window.display();
    }

}


void Window::fight_start(sf::Texture hero_texture)
{

    int menu_command;
    Menu menu(get_window());
    Fight_map fight("resources/Fight_map.tmx", this, hero_texture);
    

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
    Networking net;
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
            net.StartServer();
        }

        if (menu_command == 3) {
            //menu.start_server();
        }

        //test_server();

        main_window.display();
    }

    delete& menu;
}

void Window::addPlayer(sf::Texture& t_player, sf::Font& font, std::string clientName)
{
    std::vector<sf::IntRect> spriteRects = {
        sf::IntRect(0, 0, 120, 130),
        sf::IntRect(0, 780, 120, 130),
        sf::IntRect(0, 910, 120, 130),
        sf::IntRect(0, 520, 120, 130),
        sf::IntRect(0, 650, 120, 130)
    };
    sf::Image heroSpriteset;
    heroSpriteset.loadFromFile("resources/zel.png");
    playersVec.push_back(Hero(this, this->level, heroSpriteset, spriteRects, 200, 200, clientName));
    playersVec.back().name = clientName;
    playersVec.back().texture = t_player;
}

void Window::getUserInputData(std::string& playerName)
{
    //cout << "Enter server IP: ";
    //cin >> serverIp;
    S_Ip = "localhost";
    std::cout << endl;
    std::cout << "Enter server registration port: ";
    std::cin >> S_port;
    std::cout << endl;
    std::cout << "Enter name: ";
    std::string name;
    std::cin >> name;
    playerName = name;
};



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