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
		MsgConnect::MessageData dataConnect;
		MsgConnect::unPackData(&dataConnect, unpackedData.data(), unpackedData.size());
		uiIdClient = dataConnect.uiIdClient;
		estado = true;
		enuEstado = Aplicacion;
	}
	/*if (msgType == MESSAGE_TYPE::kLOGIN)
	{
		enuEstado = InicioPassword;
	}*/
	if (msgType == MESSAGE_TYPE::kSIGNUP)
	{
		enuEstado = Inicio;
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
		ShapesData::ShapeData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape, unpackedData.data(), unpackedData.size());
		createLine(temporalDataShape);
	}
	if (msgType == MESSAGE_TYPE::kRECT)
	{
		ShapesData::ShapeData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape, unpackedData.data(), unpackedData.size());
		createRect(temporalDataShape);
	}
	if (msgType == MESSAGE_TYPE::kCIRCLE)
	{
		ShapesData::ShapeData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape, unpackedData.data(), unpackedData.size());
		createCircle(temporalDataShape);
	}
	if (msgType == MESSAGE_TYPE::kDELETE_SHAPE)
	{
		MsgDelete commandDelete;
		MsgDelete::unPackData(&commandDelete.m_msgData, unpackedData.data(), unpackedData.size());
		cout << "Llego un delete\nId usser -> " << commandDelete.m_msgData.IdClient << "\nIdShape -> " << commandDelete.m_msgData.IdShape << endl;
		for (int i = vShapes.size() - 1; i >= 0; i--)
		{
			if (vShapes[i].idShape == commandDelete.m_msgData.IdShape)
			{
				for (int j = 0; j < vShapes[i].circleObjects.size(); j++)
				{
					delete vShapes[i].circleObjects[j];
				}
				for (int j = 0; j < vShapes[i].shapesTypes.size(); j++)
				{
					delete vShapes[i].shapesTypes[j];
				}
				vShapes.erase(vShapes.begin() + i);
			}
		}
	}
}

float DistanciaEntreDosPuntos(Vector2f& inicial, Vector2f & final)
{
	float distancia = ((pow((inicial.x - final.x), 2)) + (pow((inicial.y - final.y), 2)));
	distancia = sqrt(distancia);
	return distancia;
}

void User::createCircle(ShapesData::ShapeData& temporalDataShape)
{
	CircleShape* oTemporalCircleShape = new CircleShape();
	sf::Vector2f sizeInicial(temporalDataShape.m_posInitialX, temporalDataShape.m_posInitialY);
	sf::Vector2f sizeFinal(temporalDataShape.m_posFinalX, temporalDataShape.m_posFinalY);
	float radio = DistanciaEntreDosPuntos(sizeInicial, sizeFinal);
	oTemporalCircleShape->setRadius(radio);
	oTemporalCircleShape->setPosition(Vector2f(sizeInicial.x - radio, sizeInicial.y - radio));
	oTemporalCircleShape->setFillColor(temporalDataShape.m_cTypeColor);
	shapes newShape;
	newShape.circleObjects.push_back(oTemporalCircleShape);
	newShape.idShape = temporalDataShape.IdShape;
	vShapes.push_back(newShape);
}

void User::createRect(ShapesData::ShapeData& temporalDataShape)
{
	sf::RectangleShape* oTemporalRectangle = new RectangleShape;
	sf::Vector2f sizeInicial(temporalDataShape.m_posInitialX, temporalDataShape.m_posInitialY);
	sf::Vector2f sizeFinal(temporalDataShape.m_posFinalX, temporalDataShape.m_posFinalY);
	oTemporalRectangle->setPosition(sizeInicial);
	sf::Vector2f size = sizeFinal - sizeInicial;
	oTemporalRectangle->setSize(size);
	//temporalshape.setSize(sf::Vector2f(std::abs(size.x), std::abs(size.y)));
	oTemporalRectangle->setFillColor(temporalDataShape.m_cTypeColor);
	shapes newShape;
	newShape.shapesTypes.push_back(oTemporalRectangle);
	newShape.idShape = temporalDataShape.IdShape;
	vShapes.push_back(newShape);
}

void User::createLine(ShapesData::ShapeData& temporalDataShape)
{
	sf::RectangleShape temporalshape;
	sf::Vertex vLinePt1 = sf::Vector2f(temporalDataShape.m_posInitialX, temporalDataShape.m_posInitialY);
	vLinePt1.color = temporalDataShape.m_cTypeColor;
	sf::Vertex vLinePt2 = sf::Vector2f(temporalDataShape.m_posFinalX, temporalDataShape.m_posFinalY);
	vLinePt2.color = temporalDataShape.m_cTypeColor;
	shapes newShape;
	newShape.idShape = temporalDataShape.IdShape;
	newShape.freeLine.push_back(vLinePt1);
	newShape.freeLine.push_back(vLinePt2);
	vShapes.push_back(newShape);
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

User::~User()
{
	for (int i = 0; i < vShapes.size(); i++)
	{
		for (int j = 0; j < vShapes[i].circleObjects.size(); j++)
		{
			delete vShapes[i].circleObjects[j];
		}
		for (int j = 0; j < vShapes[i].shapesTypes.size(); j++)
		{
			delete vShapes[i].shapesTypes[j];
		}
	}
}