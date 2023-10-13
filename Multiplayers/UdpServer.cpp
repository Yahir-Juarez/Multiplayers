#include "UdpServer.h"


void Server::conexion()
{
	char in[128];
	size_t received;
	optional<sf::IpAddress> direccion;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, direccion, senderPort) != Socket::Status::Done)
		return;

	cout << "El cliente con la IP -> " << direccion.value() << ": " << quoted(in) << "\n";

	const char salida[] = "Se mando la solicitud";
	if (socket.send(salida, sizeof(salida), direccion.value(), senderPort) != Socket::Status::Done)
		return;
}

void Server::bind_port(const unsigned short* puerto)
{
	//socket.bind(Socket::AnyPort); Meojor forma de enlazar el puerto
	if (socket.bind(*puerto) != Socket::Status::Done)
		return;
}

void Server::RunUdpServer(const unsigned short puerto)
{

	//Se crea un socket
	//El puerto se hace escucha enlazandose tambien con el socket
	optional<sf::IpAddress> direccion;
	unsigned short senderPort;
	Packet paquete;
	Clock reloj;
	socket.setBlocking(false);
	bind_port(&puerto);
	conexion();
	bool servidor_activo = true;
	while (servidor_activo)
	{
		char in[128];
		size_t received;
		//Solo funciona para un cliente por ahora
		if (socket.receive(in, sizeof(in), received, direccion, senderPort) != Socket::Status::Done)
		{
			return;
		}
		else
		{
			usuario.direccion = direccion.value();
			usuario.estado = true;
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
}