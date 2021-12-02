#include "../Headers/Networking.h"
#include <thread>
#include <iostream>
#include <stdlib.h>

sf::Thread *thr;
sf::Mutex mutex;

void Networking::StartServer() {
    std::cout << std::endl << sf::IpAddress::getPublicAddress() << std::endl;
    std::cout << sf::IpAddress::getLocalAddress().toString() << std::endl;
    thr = new sf::Thread(&Networking::executionThread, this);

    thr->launch();
    Initialize();
}

void Networking::executionThread() {
    sf::Clock clock_;
    while (1) {
        mutex.lock();
        loop();
        //sf::sleep(sf::milliseconds(20));
        mutex.unlock();
    }
        
    shutdown();
}

void Networking::Initialize() {
    // bind the listener to a port
    client.bind(client_port);
    server.bind(server_port);
    //send_message("first message!");
}

void Networking::loop() {

    //server.setBlocking(0);

    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    if (server.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done){
        std::cout << std::endl << sender.getLocalAddress().toString() << " said: " << buffer << std::endl;
    }
    //std::cout << port;
}

void Networking::shutdown() {

}

void Networking::send_packet(sf::Packet packet)
{
    std::string snd_message = "z";
    client.send(snd_message.c_str(), snd_message.size() + 1, sf::IpAddress::getLocalAddress().toString(), server_port);
}

