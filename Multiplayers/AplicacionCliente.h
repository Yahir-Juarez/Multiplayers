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

constexpr int window_y = 720;
constexpr int window_x = 1280;

class App : public Packages
{
public:
	/////////////////////////////////////////////
	/// <summary>
	/// Construct.
	/// </summary>
	App();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Destruct.
	/// </summary>
	~App();
	/////////////////////////////////////////////

private:
	/////////////////////////////////////////////
	/// <summary>
	/// Start the input, update and render.
	/// </summary>
	void mainloop();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Record customer entries.
	/// </summary>
	void entrada();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Updates application states.
	/// </summary>
	void update();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Draw all the objects that are in the
	/// position.
	/// </summary>
	void render();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Check if a button is pressed to change
	/// the states the application is in or
	/// interact.
	/// </summary>
	void buttonPressed();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Check if a mousebutton is pressed and
	/// then create a temporary shape that will
	/// be displayed until the mouse is released.
	/// </summary>
	void createShapes();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Send messages special, in this case send
	/// message the delete the shapes at the
	/// server
	/// </summary>
	void commandsApp();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Draw all the figures thet arrive from
	/// the server.
	/// </summary>
	void drawShapes();
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Draws all the temporary figures that the
	/// client creates.
	/// </summary>
	void drawTemporalShapes();
	/////////////////////////////////////////////

	Color cActualColor;

	bool activeKeyBoard = true;

	ShapesData temporalShapes;
	Vector2f posInicial;
	Vector2f posFinal;
	
	bool bTemporalPositionMouse = false;
	TYPE_SHAPE::shapes eTypeMessageActual;

	
	string entradaString;

	///////////////////////////////Buttons	App////////////////////////////////

	Button inicioSesion;
	Button oLogin;
	Button keyboardOn;
	Button keyboardOff;

	Button oRectangle;
	Button oCircle;
	Button oLine;
	Button oFLine;

	/////////Colors//////////
	
	Button oColorBlack;
	Button oColorBlue;
	Button oColorCyan;
	Button oColorGreen;
	Button oColorMagenta;
	Button oColorRed;
	Button oColorYellow;
	Button oColorWhite;

	/////////////////////////

	/////////////////////////////////////////////
	/// <summary>
	/// Draw the buttons with which the client
	/// interacts.
	/// </summary>
	void renderButtonsApp();
	/////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	Clock relojTeclado;
	Clock relojButtons;
	Clock relojShapes;
	sf::RenderWindow ventana;
	sf::Event eventos;
	KeyBoard interactiveKeyBord;
	KeyBoard KbMessageForClient;

	levelKeyBoard actualKeyboard = Client;

	bool letterActivo = false;
	bool bPressButton = false;
	bool bMoveMouse = false;
	bool bCtrlZActive = false;
	User usuario;
};
