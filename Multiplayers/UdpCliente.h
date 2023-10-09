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
private:

};

class User : public ConeexionStatus {
public:
	void UdpClient(const unsigned short puerto);
private:
	sf::UdpSocket socket;
};