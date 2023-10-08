#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

class User {
public:
	sf::UdpSocket socket;
	bool estado;
	std::optional<sf::IpAddress> direccion;
private:

};