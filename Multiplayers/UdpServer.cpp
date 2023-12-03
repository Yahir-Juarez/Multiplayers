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
	//msgConeccion.m_msgData.uiIdClient = uiNewId + 1;
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

//string unpackString(Package& unpackedData)
//{
//	string data;
//	for (int i = 0; i < unpackedData.size(); i++)
//	{
//		if (unpackedData[i] == '\0')
//		{
//			data += unpackedData[i];
//			return data;
//		}
//		data += unpackedData[i];
//	}
//}

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


bool Server::outPutSend(Package& VCpackageMessage)
{
	if (socket.send(VCpackageMessage.data(), VCpackageMessage.size(), ipClient.value(), senderPort) != Socket::Status::Done)
	{
		cout << "No se mando el mensaje\n";
		return false;
	}
	return true;
}

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
	MsgMouseData::MouseData realData;
	if (msgType == MESSAGE_TYPE::kCONNECT)
	{ 
		string msg;
		msg.insert(msg.begin(), unpackedData.begin(), unpackedData.end());
		string desicionUser;
		string usser;
		string password;

		stringstream ss(msg);

		ss >> desicionUser >> usser >> password;
		cout << "entro al registro \n\a";
		//MsgSignup::unPackData(&newSignup.m_msgData, unpackedData.data(), unpackedData.size());
		if (desicionUser == "s")
		{
			if (checkUsser(usser))
			{
				cout << "Cliente ya registrado" << endl;
				//Agregar un error para cliente ya registrado, mandar kERROR
				return;
			}
			DataClientRegister newClient;
			newClient.sNameClient = usser;
			newClient.sPasswordClient = password;
			vListClients.push_back(newClient);

			/*MsgSignup oConfirmLogin;
			auto connect = oConfirmLogin.packData();
			Package finalPackage = getPackage(connect.data(), connect.size());
			outPutSend(finalPackage);*/
		}
		else
		{
			if (!(comprobateUsser(usser, password)))
			{
				cout << "No se encontro el cliente" << endl;
				//Agregar un error para cliente ya registrado, mandar kERROR
				return;
			}
		}
		conexion(usser);
		updateSendData();
	}
	//if (msgType == MESSAGE_TYPE::kLOGIN)
	//{
	//	MsgSignup::unPackData(&newSignup.m_msgData, unpackedData.data(), unpackedData.size());
	//	if (!(comprobateUsser()))
	//	{
	//		cout << "No se encontro el cliente" << endl;
	//		//Agregar un error para cliente ya registrado, mandar kERROR
	//		return;
	//	}
	//
	//	conexion();
	//	updateSendData();
	//	//MsgUsser cMsgUsuario;
	//	////MsgUsser::unPackData(&cMsgUsuario.m_msgDATA, unpackedData.data(), unpackedData.size());
	//	////cout << cMsgUsuario.m_msgDATA << endl;

	//	//cMsgUsuario.m_msgDATA = "Aceptado";
	//	//cMsgUsuario.packData();
	//	//auto connect = cMsgUsuario.packData();
	//	//Package finalPackage = getPackage(connect.data(), connect.size());
	//	//outPutSend(finalPackage);
	//	//cout << cMsgUsuario.m_msgDATA << " " << "Usser acept" << endl;
	//}
	//if (msgType == MESSAGE_TYPE::kSIGNUP)
	//{
	//	cout << "entro al registro \n\a";
	//	MsgSignup::unPackData(&newSignup.m_msgData, unpackedData.data(), unpackedData.size());
	//	if (checkUsser())
	//	{
	//		cout << "Cliente ya registrado" << endl;
	//		//Agregar un error para cliente ya registrado, mandar kERROR
	//		return;
	//	}
	//	DataClientRegister newClient;
	//	newClient.sNameClient = newSignup.m_msgData.sUsser;
	//	newClient.sPasswordClient = newSignup.m_msgData.sPassword;
	//	vListClients.push_back(newClient);

	//	MsgSignup oConfirmLogin;
	//	auto connect = oConfirmLogin.packData();
	//	Package finalPackage = getPackage(connect.data(), connect.size());
	//	outPutSend(finalPackage);
	//	/*MsgPass cMsgUsuario;
	//	cMsgUsuario.m_msgDATA = "Aceptado";
	//	cMsgUsuario.packData();
	//	auto connect = cMsgUsuario.packData();
	//	Package finalPackage = getPackage(connect.data(), connect.size());
	//	outPutSend(finalPackage);
	//	cout << cMsgUsuario.m_msgDATA << " " << "Passwor acept" << endl;*/
	//}
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
	if (msgType == MESSAGE_TYPE::kSHAPE)
	{
		ShapesData temporalDataShape;
		ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
		temporalDataShape.MSGTYPE = MESSAGE_TYPE::kSHAPE;
		if (temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::LINE)
		{
			ShapesInServer newShape;
			uiNewIdShape += 1;
			temporalDataShape.m_msgData.IdShape = uiNewIdShape;
			newShape.msgShape = temporalDataShape;
			newShape.uiIdUser = assignID();
			vShapesInServer.push_back(newShape);
			SendShapes();
		}
		if (temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::FREEDRAW)
		{
			ShapesInServer newShape;
			uiNewIdShape += 1;
			temporalDataShape.m_msgData.IdShape = uiNewIdShape;
			newShape.msgShape = temporalDataShape;
			newShape.uiIdUser = assignID();
			vShapesInServer.push_back(newShape);
			SendShapes();
		}
		if (temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::RECTANGLE)
		{
			ShapesInServer newShape;
			uiNewIdShape += 1;
			temporalDataShape.m_msgData.IdShape = uiNewIdShape;
			newShape.msgShape = temporalDataShape;
			newShape.uiIdUser = assignID();
			vShapesInServer.push_back(newShape);
			SendShapes();
		}
		if (temporalDataShape.m_msgData.typeShape == TYPE_SHAPE::shapes::CIRCLE)
		{
			ShapesInServer newShape;
			uiNewIdShape += 1;
			temporalDataShape.m_msgData.IdShape = uiNewIdShape;
			newShape.msgShape = temporalDataShape;
			newShape.uiIdUser = assignID();
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
			if (vShapesInServer[i].uiIdUser == assignID())
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
	/*for (int i = 0; i < vShapesInServer.size(); i++)
	{
		switch (vShapesInServer[i].m_msgData.MSGTYPE)
		{
		case (MESSAGE_TYPE::kCIRCLE):
		{
			ShapesData temporalDataShape;
			ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
			vShapesInServer.push_back(temporalDataShape);
			SendShapes();
			break;
		}
		default:
			break;
		}
	}*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Server::assignID()
{
	for (int i = 0; i < vActiveClients.size(); i++)
	{
		if (vActiveClients[i].clientPort == senderPort && vActiveClients[i].clientIp == ipClient)
		{
			return vActiveClients[i].IDclient;
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
		/*
		Time tiempo = reloj.getElapsedTime();
		float segundos = tiempo.asSeconds();
		if (segundos > 30)
		{
			usuario.estado = false;
		}

		if (direccion == usuario.direccion)
		{
			if (usuario.estado == true)
			{
				string entrada;
				paquete >> entrada;
				cout << "El cliente con la IP -> " << direccion.value() << " mando: " << entrada << "\n";

				paquete.clear();
				entrada = "Soy el servidor, mensaje recibido.";
				paquete << entrada << usuario.estado;

				if (socket.send(paquete, direccion.value(), senderPort) != Socket::Status::Done)
					return;
				cout << "El servidor mando: " << entrada << "\n";
			}
			else
			{
				string desconeccion = "Se te desconecto del servidor";
				bool desconeccionBool = false;

				cout << "Se desconecto al Cliente\n";

				Packet paquete;
				paquete << desconeccion << desconeccionBool;
				if (socket.send(paquete, direccion.value(), senderPort) != Socket::Status::Done)
					return;
				cout << "El servidor mando: " << desconeccion << "\n";
			}
		}
		*/
		
	}
}
