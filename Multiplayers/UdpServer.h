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
	std::optional<sf::IpAddress> clientIp;
	unsigned short clientPort;
	string usserName;
	unsigned int IDclient;
};

class Server : public Packages
{
public:
	Server();
	//~Server();
	void RunUdpServer(const unsigned short puerto);
private:
	void bind_port(const unsigned short* puerto);

	struct DataClientRegister
	{
		string sNameClient;
		string sPasswordClient;
	};

	//////////////		Verificacion de usuario		////////////////////

	void conexion();
	bool checkUsser();
	bool checkPassword();

	void updateSendData();

	MsgSignup newSignup;

	////////////////////////////////////////////////////////////////////

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
	unsigned int uiNewId = 0;
	vector<DataClientRegister> vListClients;
	vector<ClientData> vActiveClients;
	vector<ShapesData> vShapesInServer;
};
