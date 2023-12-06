#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>
#include <math.h>

#include "UdpServer.h"
#include "Packages.h"
#include "States.h"

using namespace sf;
using namespace std;

enum estadoApp { Inicio, InicioUser, InicioPassword, Aplicacion };
class User : public Packages{
public:
	struct shapes
	{
		unsigned int idShape;
		vector<sf::RectangleShape*> shapesTypes;
		vector<sf::CircleShape*> circleObjects;
		vector<sf::Vertex> freeLine;
	};
	vector<shapes> vShapes;

	unsigned int uiIdClient;

	User();
	~User();

	////////////////////////////	Verificacion de usuario		////////////////////////////////

	bool conexion();

	////////////////////////////////////////////////////////////////////////////////////////////

	bool bNewUsser = false;

	bool usuario(Package& VCpackageMessage);
	void UdpClient();

	void createRect(ShapesData::ShapeData& temporalDataShape);
	void createCircle(ShapesData::ShapeData& temporalDataShape);
	void createLine(ShapesData::ShapeData& temporalDataShape);

	/////////////////////////////////////////////
	/// <summary>
	/// Reset the clock clients.
	/// </summary>
	void restartClock();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Send ping to the clients
	/// </summary>
	void sendPing();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Check if the ping reception time is 
	/// exceeded and reset the message clock.
	/// </summary>
	void checkPingAndTimerMsg();
	/////////////////////////////////////////////

	Clock timerMsg;
	Clock timerPing;
	Clock Ping;
	bool estado = false;
	estadoApp enuEstado;
	std::optional<sf::IpAddress> ipServer;
	std::optional<sf::IpAddress> prueba;

	string msgActual;
private:
	void inPutRecive();
	void commandInput(Package& VCpackageInput, Unit16& msgType);
	sf::UdpSocket socket;
	unsigned short serverPort;
};

