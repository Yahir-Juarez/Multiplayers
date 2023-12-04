#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "UdpServer.h"
#include "Packages.h"

enum levelKeyBoard{Client, Password, Chat };

class KeyBoard : public Packages
{
public:
	/// <summary>
	/// hola
	/// </summary>
	/// <param name="actualKeyBoard"></param>
	/// <param name="actualUser"></param>
	/// <param name="event"></param>
	void inputKeyBoard(levelKeyBoard& actualKeyBoard, User& actualUser, Event& event);
	void render(sf::RenderWindow& windowDraw, sf::Vector2f vPosicionText);
	void render(sf::RenderWindow& windowDraw, sf::Vector2f vPosicionText, string message);
private:
	sf::Text atributes(sf::Vector2f vPosicionText);
	sf::Text atributes(sf::Vector2f vPosicionText, string message);
	//MsgSignup oSignup;
	MsgConnect oLoginRegister;
	void sendServer(User& actualUser);
	std::string sInput;
	sf::Clock reloj;
	sf::Font letterType;

	string m_option;
	string m_usser;
	string m_password;
};

