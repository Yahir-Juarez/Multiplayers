#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

#include "UdpServer.h"
#include "Packages.h"

enum estadoApp { Inicio, InicioUser, InicioPassword, Aplicacion };
class User : public Packages{
public:
	User();
	bool conexion();
	bool usuario(Package& VCpackageMessage);
	void UdpClient();
	bool estado = false;
	estadoApp enuEstado;
private:
	void inPutRecive();
	void commandInput(Package& VCpackageInput, Unit16& msgType);
	sf::UdpSocket socket;
	std::optional<sf::IpAddress> ipServer;
	const unsigned short serverPort = 50001;
};