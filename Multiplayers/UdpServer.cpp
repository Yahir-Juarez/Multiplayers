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
	const char salida[] = "Conectado";
	if (socket.send(salida, sizeof(salida), ipClient.value(), senderPort) != Socket::Status::Done)
	{
		cout << "No se mando el mensaje\n";
		return;
	}
	else
	{
		ClientData temporalData;
		temporalData.clientPort = senderPort;
		temporalData.clientIp = ipClient;
		ClientsData.push_back(temporalData);
	}
	cout << "se mando el mensaje\n";
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

		Vector<char> packData;
		if (isPackageValid(VCpackageInput, packData))
		{
			commandInput(packData);
			cout << "El cliente mando: ";
			for (int i = 0; i < packData.size(); i++)
			{
				cout << packData[i];
			}
			cout << endl;
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

void Server::commandInput(Package& VCpackageInput)
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
	cout << "Comando -> " << newInPut << endl;
	if (newInPut == "Coneccion?")
	{
		cout << "entro\n";
		conexion();
	}
	if (newInPut == "Aceptado")
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