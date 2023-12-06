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
	Clock cTimerPing;
};

struct ShapesInServer
{
	unsigned int uiIdUser;
	ShapesData msgShape;
};

struct DataClientRegister
{
	string sNameClient;
	string sPasswordClient;
};

class Server : public Packages
{
public:
	Server();
	~Server(){}
	void RunUdpServer(const unsigned short puerto);
private:
	void bind_port(const unsigned short* puerto);

	//////////////		Verificacion de usuario		////////////////////

	void conexion(string usser);
	bool checkUsser(string usser);
	bool checkPassword();
	void updateSendData();
	void checkUsserInServer(string usser);
	////////////////////////////////////////////////////////////////////

	void inPutRecive();
	void commandInput(Package& VCpackageInput, Unit16& msgType);
	void SendShapes();
	bool outPutSend(Package& VCpackageMessage);
	bool outPutSendGlobal(Package& VCpackageMessage);
	bool comprobateUsser(string usser, string password);
	unsigned int getID();

	/////////////////////////////////////////////
	/// <summary>
	/// Checks the elapsed time of the clients 
	/// last reduced message to decide whether 
	/// to remove it from the server or not.
	/// </summary>
	void checkPingClient();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Reset the clock clients.
	/// </summary>
	void restartClock();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Check if the client that sent the 
	/// message is on the server. 
	/// </summary>
	bool checkClientInServer();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Send ping to the clients
	/// </summary>
	void sendPing();
	/////////////////////////////////////////////

	Clock timerPing;

	unsigned int uiNewId = 0;
	unsigned int uiNewIdShape = 0;

	UdpSocket socket;
	bool estado;
	optional<sf::IpAddress> ipClient;
	const unsigned short serverPort = 50001;
	unsigned short senderPort;

	vector<DataClientRegister> vListClients;
	vector<ClientData> vActiveClients;
	vector<ShapesInServer> vShapesInServer;

	bool list_active = false;
};


//IP 192.168.100.34
//PUERTO 50001