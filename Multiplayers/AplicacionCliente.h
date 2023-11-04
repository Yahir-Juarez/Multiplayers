#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <cmath>

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
	enum typesShapes
	{
		Rectangle = 0,
		Circle,
		Line,
		FreeStroke
	}stateShape;

	void mainloop();
	void entrada();
	void update();
	void render();
	void buttonPressed();

	void typesShapes();
	void createShapes();

	sf::Color colorShapes;

	bool activeKeyBoard = true;

	ShapesData temporalShapes;
	Vector2f posInicial;
	Vector2f posFinal;
	
	bool bTemporalPositionMouse = false;

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
