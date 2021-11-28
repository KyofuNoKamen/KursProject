#pragma once
#include <SFML/Network.hpp>
#include <vector>

class Networking {
public:
	void StartServer();
	void executionThread();
private:
	sf::SocketSelector selector;
	sf::TcpListener listener;
	std::vector<sf::TcpSocket> clients;
	const unsigned short port = 7777;
	bool isAlive;
	
	void Initialize();
	void loop();
	void shutdown();
};
