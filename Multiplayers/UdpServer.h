#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>

#include "UdpCliente.h"
#include "Packages.h"
#include "States.h"

using namespace sf;
using namespace std;

struct ClientData
{
	ClientData();
	std::optional<sf::IpAddress> clientIp;
	unsigned short clientPort;
	string usserName;
	bool conected = false;
};

class Server : public Packages
{
public:
	Server();
	void RunUdpServer(const unsigned short puerto);
private:
	void bind_port(const unsigned short* puerto);
	void conexion();
	void inPutRecive();
	void commandInput(Package& VCpackageInput, Unit16& msgType);
	void SendShapes();
	bool outPutSend(Package& VCpackageMessage);
	bool comprobateUsser();
	UdpSocket socket;
	User usuario;
	bool estado;
	optional<sf::IpAddress> ipClient;
	const unsigned short serverPort = 50001;
	unsigned short senderPort;
	vector<ClientData> ClientsData;
	vector<ShapesData> vShapesInServer;
	const vector<string> vClientes = { "Yahir", "JuanCa", "Sergio", "Prince" };
	const string password = "123456";
};
