#include <SFML/Network.hpp>
#include <iostream>
#include <optional>

using std::cout;
using std::cin;
using namespace sf;
using namespace std;

void UdpClient(const unsigned short puerto)
{
	std::optional<sf::IpAddress> direccion;
	bool conectado = true;
	do
	{
		cout << "Escribe la Ip desde donde te conectas\n";
		cin >> direccion;
	} while (!direccion.has_value());
	UdpSocket socket;
	
	
	const char salida[] = "Se conecto al servidor";
	if (socket.send(salida, sizeof(salida), direccion.value(), puerto) != Socket::Status::Done)
		return;
	char entrada[128];
	size_t received;
	unsigned short senderPort;
	if (socket.receive(entrada, sizeof(entrada), received, direccion, senderPort) != Socket::Status::Done)
		return;
	cout << "El servidor mando: " << quoted(entrada) << "\n";


	while (conectado == true)
	{
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
		if (socket.receive(paquete, direccion, senderPort) != Socket::Status::Done)
			return;
		paquete >> x >> conectado;
		Time tiempo = reloj.getElapsedTime();
		float segundos = tiempo.asSeconds();
		cout << "El servidor mando: " << x << " \nEl ping fue de " << segundos << " Segundos\n";
	}
}