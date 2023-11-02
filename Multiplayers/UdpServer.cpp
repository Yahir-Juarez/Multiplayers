#include "UdpServer.h"
#include "States.h"

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

int contarLetras(const char* cadena) {
	int count = 0;
	for (int i = 0; cadena[i] != '\0'; i++) {
		count++;
	}
	return count;
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

	}
	if (msgType == MESSAGE_TYPE::kPASS)
	{

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

	}
	if (msgType == MESSAGE_TYPE::kCIRCLE)
	{

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