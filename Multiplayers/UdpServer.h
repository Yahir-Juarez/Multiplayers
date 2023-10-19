#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>

#include "UdpCliente.h"

using namespace sf;
using namespace std;

struct ClientData
{
	ClientData();
	std::optional<sf::IpAddress> clientIp;
	unsigned short clientPort;
	bool conected = false;
};

class Server{
public:
	Server();
	void RunUdpServer(const unsigned short puerto);\
private:
	void bind_port(const unsigned short* puerto);
	void conexion();
	void inPutRecive();
	void commandInput(const char* inPutData);
	UdpSocket socket;
	User usuario;
	bool estado;
	optional<sf::IpAddress> ipClient;
	const unsigned short serverPort = 50001;
	unsigned short senderPort;
	vector<string> Clientes = { "Yahir", "JuanCa", "Sergio", "Prince" /* */};
	vector<ClientData> ClientsData;
};
