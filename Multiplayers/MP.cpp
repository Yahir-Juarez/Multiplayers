#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

using namespace sf;
using namespace std;

void UdpServer_b(const unsigned short puerto)
{
	//Se crea un socket
	UdpSocket socket;
	//El puerto se hace escucha enlazandose tambien con el socket
	if (socket.bind(puerto) != Socket::Status::Done)
		return;
	char in[128];
	size_t received;
	optional<sf::IpAddress> direccion;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, direccion, senderPort) != Socket::Status::Done)
		return;
	cout << "El cliente con la IP -> " << direccion.value() << ": " << quoted(in) << "\n";

	const char salida[] = "Soy el servidor, mensaje recibido.";
	if (socket.send(salida, sizeof(salida), direccion.value(), senderPort) != Socket::Status::Done)
		return;
	cout << "El servidor mando: " << quoted(salida) << "\n";
}
void UdpClient_b(const unsigned short puerto)
{
	optional<IpAddress> direccion;
	do
	{
		cout << "Escribe la Ip desde donde te conectas\n";
		cin >> direccion;
	} while (!direccion.has_value());
	UdpSocket socket;
	const char salida[] = "Soy el cliente";
	if (socket.send(salida, sizeof(salida), direccion.value(), puerto) != Socket::Status::Done)
		return;
	cout << "El cliente mando: " << quoted(salida) << "\n";
	char entrada[128];
	size_t received;
	unsigned short senderPort;
	if (socket.receive(entrada, sizeof(entrada), received, direccion, senderPort) != Socket::Status::Done)
		return;
	cout << "El servidor mando: " << quoted(entrada) << "\n";
}

int main_2()
{
	char desicion;
	const unsigned short puerto = 50001;
	cout << "Quien manda el mensaje, Servidor (s), Cliente (c)\n";
	cin >> desicion;
	if (desicion == 's')
	{
		UdpServer_b(puerto);
	}
	else
	{
		UdpClient_b(puerto);
	}
	std::cout << "Press enter to exit..." << std::endl;
	std::cin.ignore(10000, '\n');
	std::cin.ignore(10000, '\n');

	return 0;
}