#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "UdpServer.h"
#include "Packages.h"

enum levelKeyBoard{Client, Password, Chat };

class KeyBoard : public Packages
{
public:
	void inputKeyBoard(levelKeyBoard& actualKeyBoard, User& actualUser);
	void render(sf::RenderWindow& windowDraw, int posicionX, int posicionY);
private:
	sf::Text atributes(int posicionX, int posicionY);
	void sendServer(User& actualUser);
	std::string sInput;
	sf::Clock reloj;
	sf::Font letterType;
};

