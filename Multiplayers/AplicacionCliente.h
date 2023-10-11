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

	bool tecladoActivo = true;

	string entradaString;

	unique_ptr<Button> inicioSesion;
	unique_ptr<Button> keyboardOn;
	unique_ptr<Button> keyboardOff;
	shared_ptr<Clock> relojTeclado;
	shared_ptr<Clock> relojButtons;
	std::shared_ptr<sf::RenderWindow> ventana;
	std::shared_ptr < sf::Event> eventos;

	estadoApp estado;

	bool letterActivo = false;
	shared_ptr < sf::Font > font;
	shared_ptr < sf::Text > text;
	User usuario;
};
