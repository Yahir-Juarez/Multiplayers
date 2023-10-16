#include <SFML/Network.hpp>
#include <iostream>
#include <optional>
#include <string>

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

User::User()
{
	socket.setBlocking(false);
	ipServer = IpAddress::getLocalAddress();
}

bool User::conexion()
{
	std::optional<sf::IpAddress> ipServer;
	ipServer = IpAddress::getLocalAddress();
	const unsigned short serverPort = 50001;
	if (estado == false)
	{
		const char salida[] = "Coneccion?";
		if (socket.send(salida, sizeof(salida), ipServer.value(), serverPort) != Socket::Status::Done)
		{
			return false;
		}
	}
	return estado;
}

////////////////////////Funiciones para recibir mensajes del servidor////////////////////////////////////////

void User::inPutRecive()
{
	char entrada[128];
	size_t received;
	unsigned short senderPort;
	if (socket.receive(entrada, sizeof(entrada), received, ipServer, senderPort) != Socket::Status::Done)
	{
		return;
	}
	else
	{
		commandInput(entrada);
	}
	cout << "El servidor mando: " << std::quoted(entrada) << "\n";
}

int contarLetrass(const char* cadena) {
	int count = 0;
	for (int i = 0; cadena[i] != '\0'; i++) {
		count++;
	}
	return count;
}

void User::commandInput(const char* inPutData)
{
	string newInPut;

	for (int i = 0; i < contarLetrass(inPutData); i++)
	{
		if (inPutData[i] == ' ')
		{
			i = contarLetrass(inPutData);
		}
		else
		{
			newInPut += inPutData[i];
		}
	}
	if (newInPut == "Conectado")
	{
		estado = true;
	}
	if (newInPut == "Aceptado")
	{

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool User::usuario(const char* salida)
{
	cout << salida;
	if (socket.send(salida, sizeof(salida), ipServer.value(), serverPort) != Socket::Status::Done)
	{
		return false;
	}
}

void User::UdpClient()
{
	inPutRecive();
	/*
	if (estado == true)
	{
		/*
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
		paquete >> x >> estado;
		Time tiempo = reloj.getElapsedTime();
		float segundos = tiempo.asSeconds();
		cout << "El servidor mando: " << x << " \nEl ping fue de " << segundos << " Segundos\n";
		inPutRecive();
	}
	*/
}