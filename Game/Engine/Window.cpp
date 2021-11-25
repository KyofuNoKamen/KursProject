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
    Menu menu(get_window());
    Fight_interface fight_interface(get_window()); //for test

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
                fight_start();
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

        fight_interface.draw_interface(); //for test
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            runEsc = true;
        if (isEsc == true)
        {   
            menu.draw_menu();
        }

        main_window.display();
    }

    delete &fight_interface;
}


void Window::fight_start(){

    Menu menu(get_window());
    Fight_map fight("resources/Fight_map.tmx", this);
    Fight_interface fight_interface(get_window());

    while(1){


        if (isEsc == true)
        {
            menu.draw_menu();
        }

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
            main_window.setView(*view);
            
        }

        main_window.clear();
        level->Draw(main_window);
        //hero.update();
        renderFPS();
        fight_interface.draw_interface();
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

void Window::main_menu()
{
    
}
