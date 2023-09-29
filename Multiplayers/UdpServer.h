#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

using namespace sf;
using namespace std;

class User {
public:
	UdpSocket socket;
	bool estado;
	optional<sf::IpAddress> direccion;
private:

};

class Server {
public:
	void bind_port(const unsigned short* puerto);
	void conexion(User *data);
	UdpSocket socket;
private:
	bool estado;

};

void Server::conexion(User *Data)
{
	char in[128];
	size_t received;
	optional<sf::IpAddress> direccion;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, direccion, senderPort) != Socket::Status::Done)
		return;

	Data->direccion = direccion.value();
	Data->estado = true;

	cout << "El cliente con la IP -> " << direccion.value() << ": " << quoted(in) << "\n";

	const char salida[] = "Te conectaste al servidor";
	if (socket.send(salida, sizeof(salida), direccion.value(), senderPort) != Socket::Status::Done)
		return;
}
void Server::bind_port(const unsigned short* puerto)
{
	if (socket.bind(*puerto) != Socket::Status::Done)
		return;
}