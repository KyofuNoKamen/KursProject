#include "../Headers/Networking.h"
#include <thread>


void Networking::StartServer() {
    printf("before startS");
    std::thread thr(&Networking::executionThread, this);
    
}

void Networking::executionThread() {
    Initialize();
    //while(isAlive) loop();
    printf("loop");
    loop();
    printf("shutdown");
    shutdown();
}

void Networking::Initialize() {
    isAlive = true;
    printf("i1");
    // bind the listener to a port
    if (listener.listen(port) != sf::Socket::Done) {
        printf("ERROR!Listening to port %d failed.", port);
    }

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done) {
        printf("ERROR!Failed to accept client.");
    }
    sf::Packet packet;
    packet << 1;
    printf("i3");
    client.send(packet);
}

void Networking::loop() {

    sf::TcpSocket socket;
    printf("l1");
    sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), port);
    if (status != sf::Socket::Done)
    {
        printf("Client connection failed!\n");
    }
    printf("l2");
    sf::Packet pck;
    //socket.receive(pck);
    int a=1;
    //pck >> a;
    printf("a=%d", a);
}

void Networking::shutdown() {

}

