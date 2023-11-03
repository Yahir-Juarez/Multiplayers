#include <SFML/Network.hpp>
#include <iostream>
#include <optional>
#include <string>

#include "AplicacionCliente.h"
#include "States.h"

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
		MsgConnect msgConeccion;
		msgConeccion.packData();
		auto connect = msgConeccion.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		if (socket.send(finalPackage.data(), finalPackage.size(), ipServer.value(), serverPort) != Socket::Status::Done)
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

		Package realPackage;
		if (isPackageValid(VCpackageInput, &realPackage))
		{
			Unit16 msgType = MESSAGE_TYPE::kERROR;
			Package unpackedData;
			getPackageTypeAndData(realPackage, msgType, unpackedData);

			commandInput(unpackedData, msgType);
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

void User::commandInput(Package& unpackedData, Unit16& msgType)
{
	MsgMouseData::MouseData realData;
	if (msgType == MESSAGE_TYPE::kCONNECT)
	{
		estado = true;
		enuEstado = InicioUser;
	}
	if (msgType == MESSAGE_TYPE::kUSSER)
	{
		enuEstado = InicioPassword;
	}
	if (msgType == MESSAGE_TYPE::kPASS)
	{
		enuEstado = Aplicacion;
	}
	if (msgType == MESSAGE_TYPE::kDISCONNECT)
	{

	}
	if (msgType == MESSAGE_TYPE::kCHAT)
	{

	}
	if (msgType == MESSAGE_TYPE::kMOUSESTATE)
	{
		MsgMouseData::unPackData(&realData, unpackedData.data(), unpackedData.size());
		cout << "si\n";
	}
	if (msgType == MESSAGE_TYPE::kLINE)
	{

	}
	if (msgType == MESSAGE_TYPE::kRECT)
	{
		ShapesData::ShapeData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape, unpackedData.data(), unpackedData.size());
	}
	if (msgType == MESSAGE_TYPE::kCIRCLE)
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