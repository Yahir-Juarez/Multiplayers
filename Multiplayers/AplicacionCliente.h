#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "Buttons.h"
#include "KeyBoard.h"
#include "UdpServer.h"
#include "Packages.h"
#include "States.h"

using namespace std;
using namespace sf;

constexpr int window_y = 800;
constexpr int window_x = 1200;

class App : public Packages
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

	void stateShape();
	void createShapes();
	Color cActualColor;

	bool activeKeyBoard = true;

	ShapesData temporalShapes;
	Vector2f posInicial;
	Vector2f posFinal;
	
	bool bTemporalPositionMouse = false;
	MESSAGE_TYPE::K eTypeMessageActual;

	string entradaString;
	Button inicioSesion;
	Button keyboardOn;
	Button keyboardOff;
	Clock relojTeclado;
	Clock relojButtons;
	Clock relojShapes;
	sf::RenderWindow ventana;
	sf::Event eventos;
	KeyBoard interactiveKeyBord;
	KeyBoard KbMessageForClient;

	levelKeyBoard actualKeyboard = Client;

	bool letterActivo = false;
	User usuario;
};
