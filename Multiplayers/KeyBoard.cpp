#include "KeyBoard.h"
#include "States.h"
using namespace sf;

/// <summary>
/// hola 3
/// </summary>
/// <param name="actualKeyBoard"></param>
/// <param name="actualUser"></param>
/// <param name="event"></param>
void KeyBoard::inputKeyBoard(levelKeyBoard& actualKeyBoard, User& actualUser, Event& event)
{
	sf::Time tiempo;
	const int limitCharacter = 29;
	tiempo = reloj.getElapsedTime();
	float tiempoTecla = tiempo.asSeconds();
	if (tiempoTecla > .14)
	{
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode < 128) {

				char newChar = static_cast<char>(event.text.unicode);
				if (newChar == '\b' && sInput.size() > 0)
				{
					sInput.pop_back();
					reloj.restart();
				}
				else if (newChar == '\r')
				{
					sendServer(actualUser);
					sInput.clear();
					reloj.restart();
				}
				else if (sInput.size() > limitCharacter && (actualKeyBoard == Client || actualKeyBoard == Password))
				{
					reloj.restart();
					sInput.pop_back();
				}
				else
				{
					reloj.restart();
					sInput += newChar;
				}
			}
		}
	}
}
void KeyBoard::sendServer(User& actualUser)
{
	if (actualUser.enuEstado == estadoApp::InicioUser)
	{
		actualUser.enuEstado = estadoApp::InicioPassword;
		if (actualUser.bNewUsser)
		{
			m_option = "s";
			m_usser = sInput;
			return;
		}
		m_option = "l";
		m_usser = sInput;
	}
	else if (actualUser.enuEstado == estadoApp::InicioPassword)
	{
		if (actualUser.bNewUsser)
		{
			m_password = sInput;
			string totalMsg = m_option + " " + m_usser + " " + m_password;
			oLoginRegister.m_msgData = totalMsg;
			auto connect = oLoginRegister.packData();
			Package finalPackage = getPackage(connect.data(), connect.size());
			actualUser.usuario(finalPackage);
			return;
		}
		m_password = sInput;
		string totalMsg = m_option + " " + m_usser + " " + m_password;
		oLoginRegister.m_msgData = totalMsg;
		auto connect = oLoginRegister.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		actualUser.usuario(finalPackage);
		return;
	}
	if (actualUser.enuEstado == Aplicacion)
	{
		MsgChat cMsgUsuario;
		cMsgUsuario.m_msgData = sInput;
		cMsgUsuario.packData();
		auto connect = cMsgUsuario.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		actualUser.usuario(finalPackage);
	}
}

void KeyBoard::render(sf::RenderWindow& windowDraw, sf::Vector2f vPosicionText)
{
	sf::Text stringRender = atributes(vPosicionText);
	windowDraw.draw(stringRender);
}

void KeyBoard::render(sf::RenderWindow& windowDraw, sf::Vector2f vPosicionText, string message)
{
	sf::Text stringRender = atributes(vPosicionText, message);
	windowDraw.draw(stringRender);
}

sf::Text KeyBoard::atributes(sf::Vector2f vPosicionText)
{
	unsigned int characterSize = 50;
	if (!letterType.loadFromFile("ASMAN.ttf")) {
		std::cout << "Error al cargar la fuente" << std::endl;
	}
	sf::Text text(letterType, sInput, characterSize);
	text.setPosition(vPosicionText);
	text.setFillColor(sf::Color::Black);
	return text;
}

sf::Text KeyBoard::atributes(sf::Vector2f vPosicionText, string message)
{
	unsigned int characterSize = 50;
	if (!letterType.loadFromFile("ASMAN.ttf")) {
		std::cout << "Error al cargar la fuente" << std::endl;
	}
	sf::Text text(letterType, message, characterSize);
	text.setPosition(vPosicionText);
	text.setFillColor(sf::Color::Black);
	return text;
}