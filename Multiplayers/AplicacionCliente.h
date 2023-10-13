#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "Buttons.h"
#include "UdpServer.h"

using namespace std;
using namespace sf;

constexpr int window_y = 800;
constexpr int window_x = 1200;

enum estadoApp { Inicio, InicioUser, InicioPassword, Aplicacion };

class App
{
public:
	App();
	~App();
private:
	
	void mainloop();
	void entrada();
	void update();
	void render();
	void teclado();
	void buttonPressed();

	bool tecladoActivo = false;

	string entradaString;
	Button inicioSesion;
	Button keyboardOn;
	Button keyboardOff;
	Clock relojTeclado;
	Clock relojButtons;
	sf::RenderWindow ventana;
	sf::Event eventos;

	estadoApp estado;

	bool letterActivo = false;
	sf::Font font;
	//sf::Text text;
	User usuario;
};
