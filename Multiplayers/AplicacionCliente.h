#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "UdpServer.h"

using namespace std;
using namespace sf;

constexpr int window_y = 1000;
constexpr int window_x = 2400;


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
	std::shared_ptr<sf::RenderWindow> ventana;
	std::shared_ptr < sf::Event> eventos;
	//sf::Font font;
	//sf::Text *text;
	User usuario;
};
