#include "KeyBoard.h"

using namespace sf;

void KeyBoard::inputKeyBoard(levelKeyBoard& actualKeyBoard, User& actualUser)
{
	sf::Time tiempo;
	tiempo = reloj.getElapsedTime();
	float tiempoTecla = tiempo.asSeconds();
	if (tiempoTecla > .18)
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
			sInput.clear();
			reloj.restart();
		}
	}
}

void KeyBoard::sendServer(levelKeyBoard& actualKeyBoard, User& actualUser)
{
	if (actualKeyBoard == 0)
	{
		std::string mesasageServer = "User= ";
		mesasageServer += sInput;
		actualUser.usuario(mesasageServer.c_str());
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