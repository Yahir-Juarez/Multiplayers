#include "KeyBoard.h"
#include "States.h"
using namespace sf;

void KeyBoard::inputKeyBoard(levelKeyBoard& actualKeyBoard, User& actualUser)
{
	sf::Time tiempo;
	const int limitCharacter = 29;
	tiempo = reloj.getElapsedTime();
	float tiempoTecla = tiempo.asSeconds();
	if (tiempoTecla > .14)
	{
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			sInput += "Q";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			sInput += "W";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			sInput += "E";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::R))
		{
			sInput += "R";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::T))
		{
			sInput += "T";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Y))
		{
			sInput += "Y";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::U))
		{
			sInput += "U";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::I))
		{
			sInput += "I";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::O))
		{
			sInput += "O";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::P))
		{
			sInput += "P";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			sInput += "A";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			sInput += "S";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			sInput += "D";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::F))
		{
			sInput += "F";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::G))
		{
			sInput += "G";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::H))
		{
			sInput += "H";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::J))
		{
			sInput += "J";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			sInput += "K";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::L))
		{
			sInput += "L";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			sInput += "Z";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::X))
		{
			sInput += "X";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::C))
		{
			sInput += "C";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::V))
		{
			sInput += "V";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::B))
		{
			sInput += "B";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::N))
		{
			sInput += "N";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::M))
		{
			sInput += "M";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num0))
		{
			sInput += "0";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			sInput += "1";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			sInput += "2";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			sInput += "3";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			sInput += "4";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			sInput += "5";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			sInput += "6";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num7))
		{
			sInput += "7";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num8))
		{
			sInput += "8";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num9))
		{
			sInput += "9";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			sInput += " ";
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Backspace))
		{
			sInput.pop_back();
			reloj.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			sendServer(actualUser);
			sInput.clear();
			reloj.restart();
		}	
		if (sInput.size() > limitCharacter && (actualKeyBoard == Client || actualKeyBoard == Password))
		{
			sInput.pop_back();
		}
	}
}
void KeyBoard::sendServer(User& actualUser)
{
	if (actualUser.enuEstado == estadoApp::InicioUser)
	{
		MsgUsser cMsgUsuario;
		cMsgUsuario.m_msgDATA = sInput;
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		actualUser.usuario(finalPackage);
		cout << sInput << " " << "Usuario enviado" << endl;
	}
	if (actualUser.enuEstado == estadoApp::InicioPassword)
	{
		MsgPass cMsgUsuario;
		cMsgUsuario.m_msgDATA = sInput;
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		actualUser.usuario(finalPackage);
		cout << sInput << " " << "Password enviado" << endl;
	}
	if (actualUser.enuEstado == Aplicacion)
	{
		MsgChat cMsgUsuario;
		cMsgUsuario.m_msgDATA = sInput;
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		actualUser.usuario(finalPackage);
		cout << sInput << " " << "Mensaje enviado" << endl;
	}
}

void KeyBoard::render(sf::RenderWindow& windowDraw, int posicionX, int posicionY)
{
	sf::Text stringRender = atributes(posicionX, posicionY);
	windowDraw.draw(stringRender);
}

sf::Text KeyBoard::atributes(int posicionX, int posicionY)
{
	unsigned int characterSize = 25;
	if (!letterType.loadFromFile("ASMAN.ttf")) {
		std::cout << "Error al cargar la fuente" << std::endl;
	}
	sf::Vector2f vPosicionText(posicionX, posicionY);
	sf::Text text(letterType, sInput, characterSize);
	text.setPosition(vPosicionText);
	text.setFillColor(sf::Color::Black);
	return text;
}