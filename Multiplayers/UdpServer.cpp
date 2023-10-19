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
	char entrada[128];
	size_t received;
	if (socket.receive(entrada, sizeof(entrada), received, ipClient, senderPort) != Socket::Status::Done)
	{
		return;
	}
	else
	{
		commandInput(entrada);
	}
	cout << "El cliente mando: " << entrada << "\n";
}

int contarLetras(const char* cadena) {
	int count = 0;
	for (int i = 0; cadena[i] != '\0'; i++) {
		count++;
	}
	return count;
}

void Server::commandInput(const char* inPutData)
{
	string newInPut;
	for (int i = 0; i < contarLetras(inPutData); i++)
	{
		if (inPutData[i] == ' ')
		{
			i = sizeof(inPutData);
		}
		else
		{
			newInPut += inPutData[i];
		}
	}
	cout << newInPut << endl;
	if (newInPut == "Coneccion?")
	{
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