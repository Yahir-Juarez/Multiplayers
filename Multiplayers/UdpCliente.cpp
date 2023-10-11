#include <SFML/Network.hpp>
#include <iostream>
#include <optional>


#include "AplicacionCliente.h"

using std::cout;
using std::cin;
using std::string;
using sf::IpAddress;
using sf::UdpSocket;
using sf::Socket;
using sf::Packet;
using sf::Clock;
using sf::Time;

bool User::conexion()
{
	direccion = IpAddress::getLocalAddress();
	bool conectado = true;
	if (estado == false)
	{
		socket.setBlocking(false);
		const char salida[] = "Se quiere conectar al servidor";
		if (socket.send(salida, sizeof(salida), direccion.value(), puerto) != Socket::Status::Done)
		{
			return false;
		}
		char entrada[128];
		size_t received;
		unsigned short senderPort;
		if (socket.receive(entrada, sizeof(entrada), received, direccion, senderPort) != Socket::Status::Done)
		{
			return false;
		}
		cout << "El servidor mando: " << std::quoted(entrada) << "\n";
		estado = true;
	}
	return estado;
}

bool User::usuario(const char* salida)
{
	cout << salida;
	if (socket.send(salida, sizeof(salida), direccion.value(), puerto) != Socket::Status::Done)
	{
		return false;
	}
}

void User::UdpClient()
{
	bool conectado = true;

	if (estado == true)
	{
		socket.setBlocking(false);
		string x;
		cin >> x;
		Packet paquete;
		paquete << x;
		const char salida[] = "Soy el cliente";
		Clock reloj;
		if (socket.send(paquete, direccion.value(), puerto) != Socket::Status::Done)
			return;
		cout << "El cliente mando: " << x << "\n";
		
		paquete.clear();

		unsigned short senderPort;
		if (socket.receive(paquete, direccion, senderPort) == Socket::Status::Done)
			return;
		paquete >> x >> conectado;
		Time tiempo = reloj.getElapsedTime();
		float segundos = tiempo.asSeconds();
		cout << "El servidor mando: " << x << " \nEl ping fue de " << segundos << " Segundos\n";
	}
}