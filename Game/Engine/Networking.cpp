#include "../Headers/Networking.h"
#include <thread>
#include <iostream>
#include <stdlib.h>

sf::Thread *thr;
sf::Mutex mutex;

void Networking::StartServer() {
    printf("before startS");
    std::cout << std::endl << sf::IpAddress::getPublicAddress() << std::endl;
    thr = new sf::Thread(&Networking::executionThread, this);

    thr->launch();
    Initialize();
}

void Networking::executionThread() {
    sf::Clock clock_;
    while (1) {
        mutex.lock();
        loop();
        //sf::sleep(sf::milliseconds(10));
        mutex.unlock();
    }
        
    printf("loop");
    printf("shutdown");
    shutdown();
}

void Networking::Initialize() {
    // bind the listener to a port
    client.bind(client_port);
    server.bind(server_port);

    send_message("first message!");
    send_message("second message!");
}

void Networking::loop() {



    //server.setBlocking(0);

    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    if (server.receive(buffer, sizeof(buffer), received, sender, port) == 0)
    {
        std::cout << std::endl << sender.getPublicAddress().toString() << " said: " << buffer << std::endl;
    }
    //std::cout << port;
}

void Networking::shutdown() {

}

void Networking::send_message(std::string message)
{
    std::string snd_message = message;
    //std::cout << message << std::endl;
    client.send(snd_message.c_str(), snd_message.size() + 1, "104.197.27.194", server_port);
}

