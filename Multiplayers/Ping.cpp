#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

#include "UdpServer.h"
#include "AplicacionCliente.h"
using namespace sf;
using namespace std;

int main()
{
	char desicion;
	const unsigned short puerto = 50001;
	cout << "Quien manda el mensaje, Servidor (s), Cliente (c)\n";
	cin >> desicion;
	if (desicion == 's')
	{
		Server servidor;
		servidor.RunUdpServer(puerto);
	}
	else if (desicion == 'c')
	{
		App aplicacion;
	}
	else
	{
		cout << "Error en la desiciom\n";
	}
	std::cout << "Press enter to exit..." << std::endl;
	std::cin.ignore(10000, '\n');
	std::cin.ignore(10000, '\n');
}
//Me gustaria declararle mi amor pero solo se declarar variables