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
	Package VCpackageOutput;
	std::optional<sf::IpAddress> ipServer;
	ipServer = IpAddress::getLocalAddress();
	const unsigned short serverPort = 50001;
	if (estado == false)
	{
		string sOutput = "Coneccion?";
		VCpackageOutput = getPackage(sOutput.data(), sizeof(sOutput));
		if (socket.send(VCpackageOutput.data(), VCpackageOutput.size(), ipServer.value(), serverPort) != Socket::Status::Done)
		{
			return false;
		}
	}
	return estado;
}

////////////////////////Funiciones para recibir mensajes del servidor////////////////////////////////////////

void User::inPutRecive()
{
	Vector<char> VCpackageInput;
	VCpackageInput.resize(2048);
	size_t received;
	unsigned short senderPort;
	if (socket.receive(VCpackageInput.data(), VCpackageInput.size(), received, ipServer, senderPort) != Socket::Status::Done)
	{
		return;
	}
	else
	{
		Package pRecivedPackage;
		pRecivedPackage.resize(received);
		memcpy(pRecivedPackage.data(), VCpackageInput.data(), received);
		commandInput(VCpackageInput);

		Package realPackage;
		if (isPackageValid(pRecivedPackage, &realPackage))
		{
			commandInput(pRecivedPackage);
			cout << "El servidor mando: ";
			for (int i = 0; i < pRecivedPackage.size(); i++)
			{
				cout << pRecivedPackage[i];
			}
			cout << endl;
		}
	}
	cout << "El servidor mando: ";

	////////////////////////////////////Borrar////////////////////////////////////////
	for (int i = 0; i << VCpackageInput.size(); i++)
	{
		cout << VCpackageInput[i];
	}
	cout << endl;
	//////////////////////////////////////////////////////////////////////////////////
}

int contarLetrass(const char* cadena) {
	int count = 0;
	for (int i = 0; cadena[i] != '\0'; i++) {
		count++;
	}
	return count;
}

void User::commandInput(Package& VCpackageInput)
{
	string newInPut;

	for (int i = 0; i < VCpackageInput.size(); i++)
	{
		if (VCpackageInput[i] == '\0' || VCpackageInput[i] == ' ')
		{
			i = VCpackageInput.size();
		}
		else
		{
			newInPut += VCpackageInput[i];
		}
	}
	if (newInPut == "Conectado")
	{
		estado = true;
		enuEstado = InicioUser;
	}
	if (newInPut == "Aceptado")
	{

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool User::usuario(Package& VCpackageMessage)
{
	std::optional<sf::IpAddress> ipServer;
	ipServer = IpAddress::getLocalAddress();
	const unsigned short serverPort = 50001;

	if (socket.send(VCpackageMessage.data(), VCpackageMessage.size(), ipServer.value(), serverPort) != Socket::Status::Done)
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