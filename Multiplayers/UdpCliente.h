#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

#include "UdpServer.h"

class User {
public:
	User();
	bool conexion();
	bool usuario(const char* salida);
	void UdpClient();
	bool estado = false;
private:
	void inPutRecive();
	void commandInput(const char* inPutData);
	sf::UdpSocket socket;
	std::optional<sf::IpAddress> ipServer;
	const unsigned short serverPort = 50001;
};