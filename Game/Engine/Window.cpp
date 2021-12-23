#pragma once
#include "../Headers/Window.h"
#include "../Headers/Hero.h"
#include "../Headers/Entity.h"
#include "../Headers/Enemy.h"
#include "../Headers/Mod_Heal.h"
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
Hero* hero;
vector<Hero*> playersVec;
vector<std::string> namesVec;
string clientName;
NetworkClient netC;

sf::IpAddress S_Ip = sf::IpAddress::IpAddress::LocalHost;
int S_port = 53948;

Window::Window(int resolution_x, int resolution_y, LabLevel& level, std::string name){
    create_window(resolution_x, resolution_y, name);
    view = new sf::View(sf::FloatRect(0, 0, main_window.getSize().x, main_window.getSize().y));
    //view->setCenter(sf::Vector2f(500, 500));
    main_window.setView(*view);
    setLevel(level);
    level.spawnEnemies();
    level.spawnHeals();
}

void Window::create_window(int resolution_x, int resolution_y, std::string name)
{
    Window::main_window.create(sf::VideoMode(resolution_x, resolution_y), name, sf::Style::Fullscreen);
	Window::main_window.setFramerateLimit(60);
    Window::main_window.setKeyRepeatEnabled(false);
    main_window.setVerticalSyncEnabled(1);
}

void sendData() {
    sf::Packet sendDataPacket;
    while (1)
    {
        sendDataPacket << "DATA" << hero->x << hero->y;
        netC.sendData(sendDataPacket);
        sendDataPacket.clear();
        sf::sleep(sf::milliseconds(50));
    }
}

void Window::start() 
{
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
    //hro = &hero;

    sf::Font font;
    font.loadFromFile("resources/fonts/pwscratchy1.ttf");

    hero = new Hero(this, this->level, heroSpriteset, spriteRects, 2000, 3800, "player");
    
    getUserInputData(hero->name);

    
    netC.registerOnServer(S_Ip, S_port, hero->name);

    //getUserInputData(player.name);

    netC.receiveConnectedClientsNames(namesVec);
    for (int i = 0; i < namesVec.size(); i++)
    {
        addPlayer(heroSpriteset, spriteRects, namesVec[i]);
    }

    sf::Packet receivedDataPacket;

    view->setCenter(hero->sprite.getPosition());

    fpsText.setFont(font);
    fpsText.setCharacterSize(28);
    fpsText.setFillColor(sf::Color::Red);
    
    main_window.setView(*view);

    sf::Thread thread(&sendData);
    thread.launch();

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
                view->move(sf::Vector2f(10, 0));
                //fight_start(hero/*hero.get_texture()*/);  /////////////////////////////////
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
       // fight_start();   ////////////////////



        

        if (netC.receiveData(receivedDataPacket, S_Ip, S_port) == sf::Socket::Status::Done)
        {
            if (receivedDataPacket.getDataSize() > 0)
            {
                std::string s;
                
                if (receivedDataPacket >> s)
                {
                    if (s == "NEW")
                    {
                        if (receivedDataPacket >> s)
                        {
                            if (s != clientName)
                            {
                                addPlayer(heroSpriteset, spriteRects, s);
                                namesVec.push_back(s);
                                cout << "New player connected: " << playersVec.back()->name << endl;
                            }
                        }
                    }
                    if (s == "DATA")
                    {
                        while (!receivedDataPacket.endOfPacket())
                        {
                            float x, y;
                            receivedDataPacket >> s;
                            receivedDataPacket >> x;
                            std::cout << x << std::endl;
                            receivedDataPacket >> y;
                            for (int i = 0; i < playersVec.size(); i++)
                            {
                                if (s == playersVec[i]->name)
                                {
                                    playersVec[i]->sprite.setPosition(sf::Vector2f(x, y));
                                    std::cout << playersVec[i]->x << " - " << x << std::endl;
                                    std::cout << playersVec[i]->y << " - " << y << std::endl;
                                    playersVec[i]->x = x;
                                    playersVec[i]->y = y;
                                    std::cout << "11111111111111111111111111111111111111111111" << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        

        for (int i = 0; i < playersVec.size(); i++)
        {
            playersVec[i]->sprite.setTextureRect(playersVec[i]->currentRect);
            playersVec[i]->sprite.setPosition(sf::Vector2f(playersVec[i]->x, playersVec[i]->y));
            main_window.draw(playersVec[i]->sprite);
            //main_window.draw(playersVec[i]->sprite);
        }

        if (main_window.hasFocus())
        {
            hero->update(deltatime);
            setViewCenter(hero->sprite.getPosition().x, hero->sprite.getPosition().y);
        }
        
        

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




void Window::fight_start(/*Hero* hero, */ Enemy & enemy)
{
    int menu_command;
    Menu menu(get_window());

    //Enemy squad = object Enemy with its field "enemy_squad"
    //Ally squad = object Hero with its field "hero_squad"

    /*//Creating an ally aquad
    std::vector<Entity> allySquad;
    std::vector<Enemy> ellies = level->GetAllies();  //allies = level.GetAllies() - method which will return vector of the ally objects (work in progress) 
    for (Enemy& enemy : enemies) {
        enemySquad.emplace_back(enemy);
    }*/
    
    Fight_map fight("resources/Fight_map.tmx", this, hero, enemy);/*, hero_texture,  allySquad, enemySquad);*/    //ÑÞÄÀ ÍÓÆÍÎ ÏÅÐÅÄÀÒÜ ÎÁÚÅÊÒÛ ÂÐÀÃÀ È ÃÅÐÎß!!!!
    
    while(1){

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
                view->move(sf::Vector2f(10, 0));
                //fight.draw_map();
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
        fight.update_frame();
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

void Window::checkEnemies(/*sf::Texture hero_texture*/) {
    //std::cout << "hero coordinates x " << hero->x << std::endl;
    //std::cout << "hero coordinates y " << hero->y << std::endl;
    //std::cout << "hero agility " << hero->agility << std::endl;
    //std::cout << "hero damage " << hero->damage << std::endl;
    //std::cout << "hero health " << hero->health << std::endl;
    //std::cout << "hero squad counter " << hero->squad_counter << std::endl;
    //sf::Texture hero_texture = hero->get_texture();

    std::vector<Enemy> enemies = level->GetEnemies();
    std::vector<Mod_Heal> heals = level->GetHeals();

    for (Enemy& enemy : enemies) {

        if (hero->underModificator == false) {
            if ((abs(hero->x - enemy.x) <= enemy.vissibility_distance) && (abs(hero->y - enemy.y) <= enemy.vissibility_distance)) {
                std::cout << "Checking enemy coordinates " << enemy.x << " ; " << enemy.y << std::endl;
                std::cout << "STOP RIGHT THERE!" << std::endl;
                std::cout << "____________________________________________" << std::endl;
                hero->underModificator = true;
                //Window::fight_start(enemy);
                std::cout << "You have caught by a creepy mushroom. He hits your left hand. You've lost health points" << std::endl;
                hero->health = hero->health - enemy.damage;

                std::cout << "Comparising hero and enemy characteristics..." << std::endl;
                std::cout << "Hero health : " << hero->health << " | Enemy health : " << enemy.health << std::endl;
                std::cout << "Hero damage : " << hero->damage << " | Enemy damage : " << enemy.damage << std::endl;
                std::cout << "Hero agility : " << hero->agility << " | Enemy agility : " << enemy.agility << std::endl;

                //Generator of random numbers 
                std::cout << "Checking an oportunity to escape : " << std::endl;
                int chance = (hero->agility - enemy.agility) * 2;
                std::cout << chance << std::endl;
                if (chance > 100) {
                    chance = 100;
                }
                int generated_number = rand() % 100 + 1;
                std::cout << "Generated number = " << generated_number << std::endl;
                if (generated_number < chance) {
                    std::cout << "You've managed to escape from enemy";
                }
                else {
                    std::cout << "Your try to escape failed. Enemy hited you" << std::endl;
                    hero->health = hero->health - enemy.damage;
                    std::cout << "Displaying current health points: " << hero->health << std::endl;

                }
                /////////////////
            }
        }
    }
    for (Mod_Heal& heal : heals) {
        if (hero->underModificator == false) {
            if ((abs(hero->x - heal.x) <= heal.modificator_range) && (abs(hero->y - heal.y) <= heal.modificator_range)) {
                std::cout << "Checking heal coordinates " << heal.x << " ; " << heal.y << std::endl;
                hero->underModificator = true;
                std::cout << "You have hiled by a healing potion" << std::endl;
                hero->health = hero->health + heal.healing;
                if (hero->health > 100) {
                    hero->health = 100;
                }
            }
        }
    }
}
void Window::drawEnemies() {
    LabLevel* labLevel = level;
    for (Enemy& enemy : level->GetEnemies())
        main_window.draw(enemy.sprite);
}
void Window::drawHeals() {
    LabLevel* labLevel = level;
    for (Mod_Heal& heal : level->GetHeals())
        main_window.draw(heal.sprite);
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

void Window::addPlayer(sf::Image& t_player, std::vector<sf::IntRect> spriteRects, std::string clientName)
{
    playersVec.push_back(new Hero(this, this->level, t_player, spriteRects, 200, 200, clientName));
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