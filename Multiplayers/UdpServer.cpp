#include "UdpServer.h"

ClientData::ClientData()
{

}

Server::Server()
{
	socket.setBlocking(false);
	if (socket.bind(serverPort) != Socket::Status::Done)
	{
		return;
	}
}

void Server::conexion()
{
	MsgConnect msgConeccion;
	msgConeccion.packData();
	auto connect = msgConeccion.packData();
	Package finalPackage = getPackage(connect.data(), connect.size());
	if (socket.send(finalPackage.data(), finalPackage.size(), ipClient.value(), senderPort) != Socket::Status::Done)
	{
		cout << "No se mando el mensaje\n";
		return;
	}
	ClientData temporalData;
	temporalData.clientPort = senderPort;
	temporalData.clientIp = ipClient;
	ClientsData.push_back(temporalData);
	cout << "se mando el mensaje y se agrego a la lista\n";
}

bool Server::comprobateUsser()
{
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
			/*
			cout << "El cliente mando: ";
			for (int i = 0; i < realPackage.size(); i++)
			{
				cout << realPackage[i];
			}
			cout << endl;
			*/
		}
	}
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

void Server::commandInput(Package& unpackedData, Unit16& msgType)
{
	MsgMouseData::MouseData realData;
	if (msgType == MESSAGE_TYPE::kCONNECT)
	{ 
		conexion();
	}
	if (msgType == MESSAGE_TYPE::kUSSER)
	{
		MsgUsser cMsgUsuario;
		cMsgUsuario.m_msgDATA = "Aceptado";
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		outPutSend(finalPackage);
		cout << cMsgUsuario.m_msgDATA << " " << "Usser acept" << endl;
	}
	if (msgType == MESSAGE_TYPE::kPASS)
	{
		MsgPass cMsgUsuario;
		cMsgUsuario.m_msgDATA = "Aceptado";
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		outPutSend(finalPackage);
		cout << cMsgUsuario.m_msgDATA << " " << "Passwor acept" << endl;
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
		ShapesData temporalDataShape;
		temporalDataShape.typeShape = ShapesData::typesShapes::Line;
		ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
		vShapesInServer.push_back(temporalDataShape);
		SendShapes();
	}
	if (msgType == MESSAGE_TYPE::kRECT)
	{
		ShapesData temporalDataShape;
		temporalDataShape.typeShape = ShapesData::typesShapes::Rectangle;
		ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
		vShapesInServer.push_back(temporalDataShape);
		SendShapes();
	}
	if (msgType == MESSAGE_TYPE::kCIRCLE)
	{
		ShapesData temporalDataShape;
		temporalDataShape.typeShape = ShapesData::typesShapes::Circle;
		ShapesData::unPackData(&temporalDataShape.m_msgData, unpackedData.data(), unpackedData.size());
		vShapesInServer.push_back(temporalDataShape);
		SendShapes();
	}
}

void Server::SendShapes()
{
	for (int i = 0; i < ClientsData.size(); i++)
	{
		auto connect = vShapesInServer[vShapesInServer.size() - 1].packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		if (socket.send(finalPackage.data(), finalPackage.size(), ClientsData[i].clientIp.value(), ClientsData[i].clientPort) != Socket::Status::Done)
		{
			cout << "No se mando el mensaje\n";
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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