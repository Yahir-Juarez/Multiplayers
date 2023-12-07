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
	cout << "Ingresa la IP" << endl;
	cin >> prueba;
	cout << "Ingresa el puerto" << endl;
	cin >> serverPort;
}

bool User::conexion()
{
	if (estado == false)
	{
		MsgConnect msgConeccion;
		msgConeccion.packData();
		auto connect = msgConeccion.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		if (socket.send(finalPackage.data(), finalPackage.size(), prueba.value(), serverPort) != Socket::Status::Done)
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
}

void User::commandInput(Package& unpackedData, Unit16& msgType)
{
	//MsgMouseData::MouseData realData;
	
	if (msgType == MESSAGE_TYPE::kERROR)
	{
		timerMsg.restart();
		msgActual.clear();
		estado = false;
		enuEstado = Inicio;
		msgActual.insert(msgActual.begin(), unpackedData.begin(), unpackedData.end());
		cout << msgActual << endl;
	}
	if (msgType == MESSAGE_TYPE::kPING)
	{
		restartClock();
	}
	else
	{
		restartClock();
	}
	if (msgType == MESSAGE_TYPE::kCONNECT)
	{
		MsgConnect dataConnect;
		estado = true;
		enuEstado = Aplicacion;
		timerPing.restart();
	}
	else if (msgType == MESSAGE_TYPE::kDISCONNECT)
	{
		timerMsg.restart();
		msgActual.clear();
		estado = false;
		enuEstado = Inicio;
		msgActual.insert(msgActual.begin(), unpackedData.begin(), unpackedData.end());
		cout << msgActual << endl;
	}
	else if (msgType == MESSAGE_TYPE::kCHAT)
	{
		timerMsg.restart();
		msgActual.clear();
		msgActual.insert(msgActual.begin(), unpackedData.begin(), unpackedData.end());
		cout << msgActual << endl;
	}
	else if (msgType == MESSAGE_TYPE::kSHAPE)
	{
		ShapesData::ShapeData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape, unpackedData.data(), unpackedData.size());
		if (temporalDataShape.typeShape == TYPE_SHAPE::shapes::FREEDRAW)
		{
			createLine(temporalDataShape);
		}
		if (temporalDataShape.typeShape == TYPE_SHAPE::shapes::LINE)
		{
			createLine(temporalDataShape);
		}
		if (temporalDataShape.typeShape == TYPE_SHAPE::shapes::RECTANGLE)
		{
			createRect(temporalDataShape);
		}
		if (temporalDataShape.typeShape == TYPE_SHAPE::shapes::CIRCLE)
		{
			createCircle(temporalDataShape);
		}
	}
	else if (msgType == MESSAGE_TYPE::kDELETE_SHAPE)
	{
		MsgDelete commandDelete;
		MsgDelete::unPackData(&commandDelete.m_msgData, unpackedData.data(), unpackedData.size());
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
	float sizeOutLine = 2.0f;
	sf::Vector2f sizeInicial(temporalDataShape.m_posInitialX, temporalDataShape.m_posInitialY);
	sf::Vector2f sizeFinal(temporalDataShape.m_posFinalX, temporalDataShape.m_posFinalY);

	auto diffPossVect = sizeFinal - sizeInicial;
	diffPossVect.x = std::abs(diffPossVect.x);
	diffPossVect.y = std::abs(diffPossVect.y);

	float diameter = static_cast<float>(std::max(diffPossVect.x, diffPossVect.y));
	float radius = diameter * 0.5f;

	CircleShape* oTemporalCircleShape = new CircleShape(radius);
	Vector2f sfPos(std::min(sizeInicial.x, sizeFinal.x), std::min(sizeInicial.y, sizeFinal.y));
	Vector2f scale(diffPossVect.x / diameter, diffPossVect.y / diameter);
	oTemporalCircleShape->setPosition(sfPos);
	oTemporalCircleShape->setScale(scale);
	oTemporalCircleShape->setFillColor(temporalDataShape.m_cTypeColor);;
	oTemporalCircleShape->setFillColor(Color::Transparent);
	oTemporalCircleShape->setOutlineColor(temporalDataShape.m_cTypeColor);
	oTemporalCircleShape->setOutlineThickness(sizeOutLine);
	shapes newShape;
	newShape.circleObjects.push_back(oTemporalCircleShape);
	newShape.idShape = temporalDataShape.IdShape;
	vShapes.push_back(newShape);
}

void User::createRect(ShapesData::ShapeData& temporalDataShape)
{
	float sizeOutLine = 2.0f;
	sf::RectangleShape* oTemporalRectangle = new RectangleShape;
	sf::Vector2f sizeInicial(temporalDataShape.m_posInitialX, temporalDataShape.m_posInitialY);
	sf::Vector2f sizeFinal(temporalDataShape.m_posFinalX, temporalDataShape.m_posFinalY);
	oTemporalRectangle->setPosition(sizeInicial);
	sf::Vector2f size = sizeFinal - sizeInicial;
	oTemporalRectangle->setSize(size);
	oTemporalRectangle->setFillColor(Color::Transparent);
	oTemporalRectangle->setOutlineColor(temporalDataShape.m_cTypeColor);
	oTemporalRectangle->setOutlineThickness(sizeOutLine);
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
	if (socket.send(VCpackageMessage.data(), VCpackageMessage.size(), prueba.value(), serverPort) != Socket::Status::Done)
	{
		return false;
	}
}

void User::UdpClient()
{
	inPutRecive();
	if (enuEstado == Aplicacion)
	sendPing();
	checkPingAndTimerMsg();
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

void User::restartClock()
{
	Ping.restart();
}

void User::sendPing()
{
	sf::Time tiempo;
	tiempo = timerPing.getElapsedTime();
	float timeInSeconds = tiempo.asSeconds();
	if (timeInSeconds > 3)
	{
			MsgPing newMsg;
			auto connect = newMsg.packData();
			Package finalPackage = getPackage(connect.data(), connect.size());
			usuario(finalPackage);
			timerPing.restart();
			cout << "Mando ping" << endl;	
	}
}

void User::checkPingAndTimerMsg()
{
	sf::Time tiempo;
	tiempo = timerMsg.getElapsedTime();
	float timeInSeconds = tiempo.asSeconds();
	if (timeInSeconds > 10)
	{
		msgActual.clear();
	}
	tiempo = Ping.getElapsedTime();
	timeInSeconds = tiempo.asSeconds();
	if (timeInSeconds > 20 && enuEstado == Aplicacion)
	{
		timerMsg.restart();
		msgActual.clear();
		msgActual = "Desconeccion del servidor";
		enuEstado = Inicio;
	}
}