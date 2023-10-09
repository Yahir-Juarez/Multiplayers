#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>
#include "UdpCliente.h"

using namespace sf;
using namespace std;

class Server {
public:
	void RunUdpServer(const unsigned short puerto);\
private:
	void bind_port(const unsigned short* puerto);
	void conexion(User *data);
	UdpSocket socket;
	bool estado;
	vector<string> Clientes = { "Yahir", "JuanCa", "Sergio", "Prince" };
};
