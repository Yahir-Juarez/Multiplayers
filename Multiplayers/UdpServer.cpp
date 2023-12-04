#include "UdpServer.h"
#include <sstream>

using std::stringstream;
Server::Server()
{
	socket.setBlocking(false);
	if (socket.bind(serverPort) != Socket::Status::Done)
	{
		return;
	}
}

////////////////////////////////////	Verificacion de usuario		//////////////////////////////////////

void Server::conexion(string usser)
{
	MsgConnect msgConeccion;
	msgConeccion.m_msgData = "CONECCION";
	auto connect = msgConeccion.packData();
	Package finalPackage = getPackage(connect.data(), connect.size());
	if (socket.send(finalPackage.data(), finalPackage.size(), ipClient.value(), senderPort) != Socket::Status::Done)
	{
		cout << "No se mando el mensaje\n";
		return;
	}
	uiNewId += 1;
	ClientData temporalData;
	temporalData.clientPort = senderPort;
	temporalData.clientIp = ipClient;
	temporalData.usserName = usser;
	temporalData.IDclient = uiNewId;
	vActiveClients.push_back(temporalData);
	cout << "se mando el mensaje y se agrego a la lista\n";
}

bool Server::checkUsser(string usser)
{
	for (int i = 0; i < vListClients.size(); i++)
	{
		if (vListClients[i].sNameClient == usser)
		{
			return true;
		}
	}
	return false;
}

bool Server::checkPassword()
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::comprobateUsser(string usser, string password)
{
	for (int i = 0; i < vListClients.size(); i++)
	{
		if (vListClients[i].sNameClient == usser)
		{
			if (vListClients[i].sPasswordClient == password)
			{
				return true;
			}
		}
	}
	return false;
}

void Server::bind_port(const unsigned short* puerto)
{
	if (socket.bind(*puerto) != Socket::Status::Done)
		return;
}

///////////////////////Funiciones para recibir mensajes del servidor////////////////////////////////////////

void Server::inPutRecive()
{
	Vector<char> VCpackageInput;
	VCpackageInput.resize(2048);
	size_t received;
	if (socket.receive(VCpackageInput.data(), VCpackageInput.size(), received, ipClient, senderPort) != Socket::Status::Done)
	{
		return;
	}
	Package pRecivedPackage;
	pRecivedPackage.resize(received);
	memcpy(pRecivedPackage.data(), VCpackageInput.data(), received);

	Package realPackage;
	if (!(isPackageValid(pRecivedPackage, &realPackage)))
	{
		return;
	}
	Unit16 msgType = MESSAGE_TYPE::kERROR;
	Package unpackedData;
	getPackageTypeAndData(realPackage, msgType, unpackedData);

	commandInput(unpackedData, msgType);
}

/////////////////////////////////// Mensajes privados /////////////////////////////////////////////////////

bool Server::outPutSend(Package& VCpackageMessage)
{
	if (socket.send(VCpackageMessage.data(), VCpackageMessage.size(), ipClient.value(), senderPort) != Socket::Status::Done)
	{
		cout << "No se mando el mensaje\n";
		return false;
	}
	return true;
}

/////////////////////////////////// Mensajes globales /////////////////////////////////////////////////////

bool Server::outPutSendGlobal(Package& VCpackageMessage)
{
	for (int i = 0; i < vActiveClients.size(); i++)
	{
		if (socket.send(VCpackageMessage.data(), VCpackageMessage.size(), vActiveClients[i].clientIp.value(), vActiveClients[i].clientPort) != Socket::Status::Done)
		{
			cout << "No se mando el mensaje\n";
		}
	}
	return true;
}

void Server::commandInput(Package& unpackedData, Unit16& msgType)
{
	//MsgMouseData::MouseData realData;
	if (msgType == MESSAGE_TYPE::kCONNECT)
	{ 
		string msg;
		msg.insert(msg.begin(), unpackedData.begin(), unpackedData.end());
		string desicionUser;
		string usser;
		string password;

		stringstream ss(msg);

		ss >> desicionUser >> usser >> password;

		if (desicionUser == "s")
		{
			if (checkUsser(usser))
			{
				MsgError newMsg;
				newMsg.m_msgData = "Cliente ya existente";
				auto connect = newMsg.packData();
				Package finalPackage = getPackage(connect.data(), connect.size());
				outPutSend(finalPackage);
				return;
			}
			DataClientRegister newClient;
			newClient.sNameClient = usser;
			newClient.sPasswordClient = password;
			vListClients.push_back(newClient);
		}
		else
		{
			if (!(comprobateUsser(usser, password)))
			{
				MsgError newMsg;
				newMsg.m_msgData = "Wrong Password or Usser";
				auto connect = newMsg.packData();
				Package finalPackage = getPackage(connect.data(), connect.size());
				outPutSend(finalPackage);
				return;
			}
			checkUsserInServer(usser);
		}
		conexion(usser);
		updateSendData();
	}
	if (msgType == MESSAGE_TYPE::kCHAT)
	{
		string msg;
		msg.insert(msg.begin(), unpackedData.begin(), unpackedData.end());
		MsgChat newMsg;
		newMsg.m_msgData = msg;
		auto connect = newMsg.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		outPutSendGlobal(finalPackage);
	}
	if (msgType == MESSAGE_TYPE::kSHAPE)
	{
		ShapesData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
		temporalDataShape.MSGTYPE = MESSAGE_TYPE::kSHAPE;
		if (temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::LINE || 
			temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::FREEDRAW ||
			temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::RECTANGLE ||
			temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::CIRCLE)
		{
			ShapesInServer newShape;
			uiNewIdShape += 1;
			temporalDataShape.m_msgData.IdShape = uiNewIdShape;
			newShape.msgShape = temporalDataShape;
			newShape.uiIdUser = getID();
			vShapesInServer.push_back(newShape);
			SendShapes();
		}
	}
	if (msgType == MESSAGE_TYPE::kDELETE_SHAPE)
	{
		MsgDelete commandDelete;
		MsgDelete::unPackData(&commandDelete.m_msgData, unpackedData.data(), unpackedData.size());
		for (int i = vShapesInServer.size() - 1; i >= 0; i--)
		{
			if (vShapesInServer[i].uiIdUser == getID())
			{
				commandDelete.m_msgData.IdShape = vShapesInServer[i].msgShape.m_msgData.IdShape;
				vShapesInServer.erase(vShapesInServer.begin() + i);
				break;
			}
		}
		auto connect = commandDelete.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		outPutSendGlobal(finalPackage);
	}
}

void Server::SendShapes()
{
	for (int i = 0; i < vActiveClients.size(); i++)
	{
		auto connect = vShapesInServer[vShapesInServer.size() - 1].msgShape.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		if (socket.send(finalPackage.data(), finalPackage.size(), vActiveClients[i].clientIp.value(), vActiveClients[i].clientPort) != Socket::Status::Done)
		{
			cout << "No se mando el mensaje\n";
		}
	}
}

void Server::updateSendData()
{
	for (int i = 0; i < vShapesInServer.size(); i++)
	{
		auto connect = vShapesInServer[i].msgShape.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		if (socket.send(finalPackage.data(), finalPackage.size(), vActiveClients[vActiveClients.size() - 1].clientIp.value(), vActiveClients[vActiveClients.size() - 1].clientPort) != Socket::Status::Done)
		{
			cout << "No se mando el mensaje\n";
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Server::getID()
{
	for (int i = 0; i < vActiveClients.size(); i++)
	{
		if (vActiveClients[i].clientPort == senderPort && vActiveClients[i].clientIp == ipClient)
		{
			return vActiveClients[i].IDclient;
		}
	}
}

void Server::checkUsserInServer(string usser)
{
	for (int i = vActiveClients.size() - 1; i >= 0; i--)
	{
		if (vActiveClients[i].usserName == usser)
		{
			MsgDisconnect newMsg;
			auto connect = newMsg.packData();
			Package finalPackage = getPackage(connect.data(), connect.size());
			if (socket.send(finalPackage.data(), finalPackage.size(), vActiveClients[i].clientIp.value(), vActiveClients[i].clientPort) != Socket::Status::Done)
			{
				cout << "No se mando el mensaje\n";
				return;
			}
			vActiveClients.erase(vActiveClients.begin() + i);
			break;
		}
	}

}

void Server::RunUdpServer(const unsigned short puerto)
{

	//Se crea un socket
	//El puerto se hace escucha enlazandose tambien con el socket
	Packet paquete;
	Clock reloj;
	bool servidor_activo = true;
	while (servidor_activo == true)
	{
		inPutRecive();
		if (Keyboard::isKeyPressed(Keyboard::L))
		{
			if (list_active == false)
			{
				for (int i = 0; i < vListClients.size(); i++)
				{
					cout << "Cliente	|" << vListClients[i].sNameClient << "|			 Password	|" << vListClients[i].sPasswordClient << endl;
				}
				for (int i = 0; i < vShapesInServer.size(); i++)
				{
					cout << "Id Shape: " << vShapesInServer[i].msgShape.m_msgData.IdShape << " Tipo de figura: " << vShapesInServer[i].msgShape.MSGTYPE << endl;
				}
				list_active = true;
			}
		}
		else
		{
			list_active = false;
		}	
	}
}


