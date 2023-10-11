#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

#include "UdpServer.h"

class ConeexionStatus {
public:
	bool estado = false;
	std::optional<sf::IpAddress> direccion;
	const unsigned short puerto = 50001;
private:

};

class User : public ConeexionStatus {
public:
	bool conexion();
	bool usuario(const char* salida);
	void UdpClient();
private:
	sf::UdpSocket socket;
};