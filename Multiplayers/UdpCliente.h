#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>

#include "UdpServer.h"
#include "Packages.h"
#include "States.h"

using namespace sf;
using namespace std;

enum estadoApp { Inicio, InicioUser, InicioPassword, Aplicacion };
class User : public Packages{
public:
	User();
	bool conexion();
	bool usuario(Package& VCpackageMessage);
	void UdpClient();

	void createRect(ShapesData::ShapeData& temporalDataShape);
	sf::Color TypeColor(ShapesData::ShapeData& temporalDataShape);
	vector<sf::RectangleShape> shapesTypes;
	bool estado = false;
	estadoApp enuEstado;
	std::optional<sf::IpAddress> ipServer;
private:
	void inPutRecive();
	void commandInput(Package& VCpackageInput, Unit16& msgType);
	sf::UdpSocket socket;
	const unsigned short serverPort = 50001;
};