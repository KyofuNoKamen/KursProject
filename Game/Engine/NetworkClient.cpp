#include "../Headers/NetworkClient.h"

NetworkClient::NetworkClient()
{
}

sf::Socket::Status NetworkClient::init(unsigned short preferablePort)
{
	sf::Socket::Status status = dataSocket.bind(preferablePort);

	if (status == sf::Socket::Status::Done)
	{
		cout << "init(): Successfully binded to port: " << dataSocket.getLocalPort() << endl;
		return sf::Socket::Status::Done;
	}
	else
	{
		cout << "(!)init(): Failed to bind passed preferred port\n";
		do
		{
			unsigned short newPort = sf::Socket::AnyPort;
			cout << "init(): Trying to bind other port - " << newPort << endl;
			status = dataSocket.bind(newPort);
			if (status != sf::Socket::Status::Done)
				cout << "(!)init(): Failed to bind other port. Retrying...\n";

		} while (status != sf::Socket::Done);

		cout << "init(): Successfully binded to other port - " << dataSocket.getLocalPort() << endl;
		return sf::Socket::Status::Done;
	}
}

sf::Socket::Status NetworkClient::registerOnServer(sf::IpAddress serverIp, unsigned short serverRegPort, string clientName)
{
	if (connectRegTcpSocket(serverIp, serverRegPort) != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

	if (sendClientRecipientData(clientName) != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

	if (recieveDedicatedDataServerPort() != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

}

sf::Socket::Status NetworkClient::receiveConnectedClientsNames(vector<string>& namesVec)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;

	if (regSocket.receive(tempPacket) == sf::Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			while (!tempPacket.endOfPacket())
			{
				string name;
				if (tempPacket >> name)
				{
					if (name == "FIRST")
					{
						"receiveConnectedClientsNames(): No clients are connected, you are first\n";
						return sf::Socket::Status::Done;
					}
					namesVec.push_back(name);
				}
				else
				{
					cout << "(!)receiveConnectedClientsNames() : Failed to read packet\n";
					return sf::Socket::Status::Error;
				}
			}
			cout << "receiveConnectedClientsNames() :Client names read\n";
			/*for (int i = 0; i < namesVec.size(); i++)
			{
				cout << namesVec[i];
			}
			cout << endl;*/
			return sf::Socket::Status::Done;

		}
		else cout << "(!)receiveConnectedClientsNames(): Receives packet is empty, ensure that packet contains: (string name1 << string name2 << ...) or \"FIRST\" if it's first connected client\n";
	}
	else cout << "(!)receiveConnectedClientsNames(): Failed to receive clients names\n";

	return sf::Socket::Status::Error;
}

sf::Socket::Status NetworkClient::receiveData(sf::Packet& dataPacket, sf::IpAddress S_Ip, unsigned short S_dataPort)
{
	if (dataSocket.isBlocking())dataSocket.setBlocking(false);

	if (dataSocket.receive(dataPacket, S_Ip, S_dataPort) == sf::Socket::Status::Done)
	{
		if (dataPacket.getDataSize() > 0)
		{
			//cout << "receiveData(): Data received\n";
			return sf::Socket::Status::Done;
		}
		else
		{
			cout << "(!)receiveData(): Received packet is empty\n";
			return sf::Socket::Status::Error;
		}
	}
	return sf::Socket::Status::NotReady;
}

sf::Socket::Status NetworkClient::sendData(sf::Packet dataPacket)
{
	if (sendRateTimer.getElapsedTime().asMilliseconds() > sendRate)
	{
		if (dataSocket.isBlocking())dataSocket.setBlocking(false);

		if (sendPacket.getDataSize() == 0) sendPacket = dataPacket;

		sf::IpAddress tempIp = S_Ip;
		unsigned short tempDataPort = S_dataPort;
		if (dataSocket.send(sendPacket, tempIp, tempDataPort) == sf::Socket::Status::Done)
		{
			sendPacket.clear();
			sendRateTimer.restart();
			return sf::Socket::Status::Done;
		}
		else return sf::Socket::Status::NotReady;
	}
	else return sf::Socket::Status::NotReady;
}

void NetworkClient::setSendFreq(sf::Int32 milliseconds)
{
	sendRate = milliseconds;
}

sf::Socket::Status NetworkClient::connectRegTcpSocket(sf::IpAddress serverIp, unsigned short serverRegPort)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	if (regSocket.connect(serverIp, serverRegPort, sf::seconds(10)) == sf::Socket::Status::Done)
	{
		cout << "connectRegTcpSocket(): Connected to server\n";
		S_Ip = serverIp;
		S_dataPort = serverRegPort;
		return sf::Socket::Status::Done;
	}
	else
	{
		cout << "(!)connectRegTcpSocket(): Error connecting to server!\n";
		return sf::Socket::Status::Error;
	}
}

sf::Socket::Status NetworkClient::sendClientRecipientData(string clientName)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;
	tempPacket << clientName << static_cast<sf::Uint16>(dataSocket.getLocalPort());

	if (regSocket.send(tempPacket) == sf::Socket::Status::Done)
	{
		cout << "sendClientRecipientData(): Successfully sent client recipient data\n";
		return sf::Socket::Status::Done;
	}
	else
	{
		cout << "(!)sendClientRecipientData(): Failed to send client recipient data\n";
		return sf::Socket::Status::Error;
	}
}

sf::Socket::Status NetworkClient::recieveDedicatedDataServerPort()
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;

	if (regSocket.receive(tempPacket) == sf::Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			if (tempPacket.getDataSize() == sizeof(sf::Uint16))
			{
				if (tempPacket >> S_dataPort)
				{
					cout << "recieveDedicatedDataServerPort(): Successfully received data client-dedicated port of a server - " << S_dataPort << endl;
					return sf::Socket::Status::Done;
				}
				else cout << "(!)recieveDedicatedDataServerPort(): Failed to read from received packet\n";
			}
			else cout << "(!)recieveDedicatedDataServerPort(): Invalid packet size, ensure that server sends only Uint16 var\n";
		}
		else cout << "(!)recieveDedicatedDataServerPort(): Received packet is empty\n";
	}
	else cout << "(!)recieveDedicatedDataServerPort(): Failed to receive client-dedicated port of a server\n";

	return sf::Socket::Status::Error;
}
