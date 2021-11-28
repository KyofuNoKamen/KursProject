#pragma once
#include <SFML/Network.hpp>
#include <vector>

class Networking {
public:
	void StartServer();
	void executionThread();
private:
	sf::SocketSelector selector;
	sf::UdpSocket client;
	sf::UdpSocket server;
	std::vector<sf::TcpSocket> clients;
	unsigned short client_port = 55001;
	unsigned short server_port = 55002;
	bool isAlive;
	
	void Initialize();
	void loop();
	void shutdown();

	void send_message(std::string message);

};
