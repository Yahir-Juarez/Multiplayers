#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "Buttons.h"
#include "KeyBoard.h"
#include "UdpServer.h"

using namespace std;
using namespace sf;

constexpr int window_y = 800;
constexpr int window_x = 1200;

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
	void buttonPressed();

	bool activeKeyBoard = true;

	string entradaString;
	Button inicioSesion;
	Button keyboardOn;
	Button keyboardOff;
	Clock relojTeclado;
	Clock relojButtons;
	sf::RenderWindow ventana;
	sf::Event eventos;
	KeyBoard interactiveKeyBord;

	levelKeyBoard actualKeyboard = Client;

	bool letterActivo = false;
	User usuario;
};
